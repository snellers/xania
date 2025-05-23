/************************************************************************/
/*  Xania (M)ulti(U)ser(D)ungeon server source code                     */
/*  (C) 2025 Xania Development Team                                     */
/*  See the header to file: merc.h for original code copyrights         */
/************************************************************************/
#pragma once

#include "Ban.hpp"
#include "Logging.hpp"
#include "common/Time.hpp"
#include "common/doorman_protocol.h"

struct AreaList;
struct Configuration;
struct DescriptorList;
struct HelpList;
struct Interpreter;
struct NoteHandler;
struct Socials;
struct TimeInfoData;

struct Mud {
    virtual ~Mud() = default;
    virtual Configuration &config() = 0;
    virtual DescriptorList &descriptors() = 0;
    virtual Interpreter &interpreter() = 0;
    virtual Logger &logger() = 0;
    virtual Bans &bans() = 0;
    virtual AreaList &areas() = 0;
    virtual HelpList &help() = 0;
    virtual Socials &socials() = 0;
    virtual NoteHandler &notes() = 0;
    virtual bool send_to_doorman(const Packet *p, const void *extra) const = 0;
    virtual TimeInfoData &current_tick() = 0;
    virtual Time boot_time() const = 0;
    virtual Time current_time() const = 0;
    virtual void terminate(const bool close_sockets) = 0;
    virtual bool toggle_wizlock() = 0;
    virtual bool toggle_newlock() = 0;
    virtual size_t max_players_today() const = 0;
    virtual void reset_max_players_today() = 0;
    virtual void send_tips() = 0;
};
