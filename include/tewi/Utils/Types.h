#pragma once

#include "asl/types"

namespace tewi
{
    using Width = asl::constrained_type<asl::num, asl::lower_limit<asl::num, 0>,
                                        struct WidthTag>;

    using Height =
        asl::constrained_type<asl::num, asl::lower_limit<asl::num, 0>,
                              struct HeightTag>;
} // namespace tewi
