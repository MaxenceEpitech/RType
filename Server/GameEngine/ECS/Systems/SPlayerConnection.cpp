//
// Created by max on 27/11/18.
//

#include <CSprite.hpp>
#include <Packet.hpp>
#include <CPlayer.hpp>
#include "SPlayerConnection.hpp"
#include "EntityManager.hpp"
#include "CPosition.hpp"
#include "CDirection.hpp"
#include "CSpeed.hpp"
#include "CHealth.hpp"
#include "CLevel.hpp"
#include "PacketCreator.hpp"
#include "PacketUnpacker.hpp"

namespace RType {

    SPlayerConnection::SPlayerConnection(std::shared_ptr<ComponentManager> componentManager,
                                         std::shared_ptr<EntityManager> entityManager,
                                         std::shared_ptr<NetworkHandler> networkHandler)
            : ASystem(componentManager, entityManager), _checkedId(0), _init(false), _amountPlayers(0) {
        _networkHandler = networkHandler;
    }

    void SPlayerConnection::update(std::shared_ptr<AComponent> component) {
        if (_init == false) {
            _init = true;
            checkNewConnection();
        }
        if (_checkedId == component->getId()) {
            checkNewConnection();
            checkPlayerAction();
        }
        (void) component; // Unused param
    }

    void SPlayerConnection::checkNewConnection() {
        if (_amountPlayers < _networkHandler->getPlayerData().size()) {
            newPlayerConnection();
            _amountPlayers = _networkHandler->getPlayerData().size();
        } else if (_amountPlayers > _networkHandler->getPlayerData().size()) {
            std::cout << "A PLAYER HAS DISCONNEDTED" << std::endl;
            removePlayerConnection();
            _amountPlayers = _networkHandler->getPlayerData().size();
        }
    }

    bool SPlayerConnection::playerIdContain(Id id) {
        for (PlayerIds playerIds : _players) {
            if (playerIds.playerId == id) {
                return true;
            }
        }
        return false;
    }

    void SPlayerConnection::newPlayerConnection() {
        std::cout << "New player added" << std::endl;
        Id newPlayerId = 0;
        _entityManager->CreateEntity(EEntity::player);
        for (auto &data : _networkHandler->getPlayerData()) {
            if (data.playerEntityId == -1) {
                newPlayerId = genPlayerId();
                data.playerEntityId = newPlayerId;
                std::cout << "New Player unitialized found = -1 new Id = " << newPlayerId << std::endl;
            }
        }

        std::cout << "new Player Id Generated = "
                  << newPlayerId << " Newplayer Entity Id = " << _entityManager->getLastEntityId() << std::endl;

        _players.push_back(PlayerIds{_entityManager->getLastEntityId(), newPlayerId});
        setPlayerSpriteId(newPlayerId);
        setPlayerConnectionId(newPlayerId);
    }

    Id SPlayerConnection::genPlayerId() {
        Id generated = 1;

        for (PlayerIds id : _players) {
            if (id.playerId != generated)
                return generated;
            generated++;
        }
        return generated;
    }

    void SPlayerConnection::setPlayerConnectionId(Id id) {
        std::shared_ptr<AComponent> component = _entityManager->getComponentFromEntity(EComponent::player,
                                                                                       _entityManager->getLastEntityId());
        if (auto cPlayer = std::dynamic_pointer_cast<CPlayer>(component)) {
            cPlayer->setTextureId(id);
        }
    }

    void SPlayerConnection::setPlayerSpriteId(Id id) {
        auto component = _entityManager->getComponentFromEntity(EComponent::sprite, _entityManager->getLastEntityId());
        if (auto cSprite = std::dynamic_pointer_cast<CSprite>(component)) {
            std::cout << "Changing Sprite Id " << std::endl;
            cSprite->setSize(SVector2d{150, 75});
            switch (id) {
                case 1:
                    cSprite->setId(RType::Textures::ID::PLAYER_1);
                    break;
                case 2:
                    cSprite->setId(RType::Textures::ID::PLAYER_2);
                    break;
                case 3:
                    cSprite->setId(RType::Textures::ID::PLAYER_3);
                    break;
                case 4:
                    cSprite->setId(RType::Textures::ID::PLAYER_4);
                    break;
            }
        }
    }

    void SPlayerConnection::removePlayerConnection() {
        for (std::list<PlayerIds>::iterator it = _players.begin(); it != _players.end(); it++) {
            if (!datumContain((*it).playerId)) {
                _entityManager->removeEntity((*it).entityId);
                it = _players.erase(it);
                break;
            }

        }
    }

    bool SPlayerConnection::datumContain(Id id) {
        for (auto &data : _networkHandler->getPlayerData()) {
            if (data.playerEntityId == (int) id)
                return true;
        }
        return false;
    }

    void SPlayerConnection::checkPlayerAction() {
        for (RType::player_datum_t &datum : _networkHandler->getPlayerData()) {
            Id entityId = getEntityIdFromPlayerId(datum.playerEntityId);
            if (auto comp = _entityManager->getComponentFromEntity(EComponent::health, entityId)) {
                if (auto hp = std::dynamic_pointer_cast<CHealth>(comp)) {
                    Packet::Health health;
                    health.currentHealth = hp->getHealth();
                    health.maxHealth = 50;
                    auto clvl = _componentManager->getComponents().front();
                    auto lvl = std::dynamic_pointer_cast<CLevel>(clvl);
                    health.level = lvl->getLevel();
                    auto packet = Packet::Creator::MakeHealth(health);
                    _networkHandler->Send(datum, packet);
                }
            }
            if (_entityManager->getComponentFromEntity(EComponent::health, entityId) == nullptr) {
                auto packet = Packet::Creator::MakeGameOver();
                _networkHandler->Send(datum, packet);
            }
            switch (Packet::GetEnum(datum.packet)) {
                case (Packet::ACTIONS) :
                    try {
                        handleActions(Packet::Unpacker::UnpackActions(datum.packet), datum);
                    } catch (std::exception &e) {
                        std::cerr << "Wrong packet : " << e.what() << std::endl;
                    }
                    datum.packet.clear();
                    break;
                default:
                    break;
            }
        }
    }

    void SPlayerConnection::handleActions(Packet::Actions actions, player_datum_t &player) {
        Id id = getEntityIdFromPlayerId(player.playerEntityId);
        if (auto component = _entityManager->getComponentFromEntity(EComponent::position, id)) {
            if (auto pos = std::dynamic_pointer_cast<CPosition>(component)) {
                for (auto action : actions) {
                    switch (action) {
                        case (Packet::Action::UP):
                            pos->moveUp(6);
                            break;
                        case (Packet::Action::DOWN):
                            pos->moveDown(6);
                            break;
                        case (Packet::Action::LEFT):
                            pos->moveLeft(6);
                            break;
                        case (Packet::Action::RIGHT):
                            pos->moveRight(6);
                            break;
                        case (Packet::Action::SHOOT):
                            fireAction(SVector2d{pos->getPosition().x, pos->getPosition().y + 20});
                            break;
                        case (Packet::Action::NOACTION):
                            break;
                    }
                }
            }
        }
    }

    Id SPlayerConnection::getEntityIdFromPlayerId(Id id) {
        for (std::list<PlayerIds>::iterator it = _players.begin(); it != _players.end(); it++) {
            if ((*it).playerId == id)
                return (*it).entityId;
        }
        return (0);
    }

    void SPlayerConnection::fireAction(SVector2d pos) {
        _entityManager->CreateEntity(EEntity::missile);
        Id id = _entityManager->getLastEntityId();
        auto component = _entityManager->getComponentFromEntity(EComponent::direction, id);
        if (auto cDir = std::dynamic_pointer_cast<CDirection>(component)) {
            cDir->setDirection(0);
        }
        component = _entityManager->getComponentFromEntity(EComponent::position, id);
        if (auto cPos = std::dynamic_pointer_cast<CPosition>(component)) {
            cPos->setPosition(pos);
        }
        component = _entityManager->getComponentFromEntity(EComponent::speed, id);
        if (auto speed = std::dynamic_pointer_cast<CSpeed>(component)) {
            speed->setSpeed(5);
        }
        component = _entityManager->getComponentFromEntity(EComponent::sprite, id);
        if (auto sprite = std::dynamic_pointer_cast<CSprite>(component)) {
            sprite->setId(Textures::ID::ALLY_MISSILE); // set missile
            sprite->setSize(SVector2d{59, 14});
        }
    }

} // RType