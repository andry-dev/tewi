#pragma once

#include "asl/types"

namespace tewi
{
    using Width = asl::constrained_type<
                    asl::mut_num,
                    asl::lower_limit<asl::mut_num, 0>,
                    struct WidthTag>;

    using Height = asl::constrained_type<
                    asl::mut_num,
                    asl::lower_limit<asl::mut_num, 0>,
                    struct HeightTag>;
}
