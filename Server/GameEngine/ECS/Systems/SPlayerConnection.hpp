//
// Created by max on 27/11/18.
//

#ifndef SERVER_SPLAYERCONNECTION_HPP
#define SERVER_SPLAYERCONNECTION_HPP

#include <list>
#include <iostream>
#include <Packet.hpp>

#include "ASystem.hpp"
#include "NetworkHandler.hpp"
#include "Vector.hpp"

namespace RType {
    struct PlayerIds {
        Id entityId;
        Id playerId;
    };

    class SPlayerConnection : public ASystem {
    public:
        SPlayerConnection(std::shared_ptr<ComponentManager> componentManager,
                          std::shared_ptr<EntityManager> entityManager, std::shared_ptr<NetworkHandler> networkHandler);

        void update(std::shared_ptr<AComponent> component);
        void checkNewConnection();
        void newPlayerConnection();
        void removePlayerConnection();
        void checkPlayerAction();
        void handleActions(Packet::Actions actions, player_datum_t &player);
        void setPlayerSpriteId(Id id);
        void setPlayerConnectionId(Id id);
        void fireAction(SVector2d pos);
        Id getEntityIdFromPlayerId(Id id);
        Id genPlayerId();
        bool datumContain(Id id);

        bool playerIdContain(Id id);

    private:
        std::shared_ptr<NetworkHandler> _networkHandler;
        Id _checkedId;
        bool _init;
        unsigned int _amountPlayers;
        std::list<PlayerIds> _players;

    };
} // RType


#endif //SERVER_SPLAYERCONNECTION_HPP
