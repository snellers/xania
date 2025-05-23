/************************************************************************/
/*  Xania (M)ulti(U)ser(D)ungeon server source code                     */
/*  (C) 2025 Xania Development Team                                     */
/*  See the header to file: merc.h for original code copyrights         */
/************************************************************************/
#pragma once

#include <string>

// tip wizard type - OG Faramir Sep 21 1998
class Tip {
    std::string tip_;

public:
    explicit Tip(std::string tip) : tip_(std::move(tip)) {}

    [[nodiscard]] const std::string &tip() const noexcept { return tip_; }

    [[nodiscard]] static Tip from_file(FILE *fp);
};
