//
// Created by aurailus on 11/07/19.
//

#pragma once

enum class NetState {
    UNINITIALIZED,
    FAILED_CONNECT,
    ENET_ERROR,
    CLIENT,
    HOST,
    CLOSED
};

