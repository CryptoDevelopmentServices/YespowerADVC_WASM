#include <stdint.h>
#include <string.h>
#include "yespower.h"

int yespower_hash(const char *input, char *output) {
    uint32_t time = ((uint32_t)input[68]) |
                    ((uint32_t)input[69] << 8) |
                    ((uint32_t)input[70] << 16) |
                    ((uint32_t)input[71] << 24);

    static const yespower_params_t yespower_0_5 = {
        .version = YESPOWER_0_5,
        .N = 4096,
        .r = 16,
        .pers = (const uint8_t *)"Client Key",
        .perslen = 10
    };

    static const yespower_params_t yespower_1_0 = {
        .version = YESPOWER_1_0,
        .N = 2048,
        .r = 32,
        .pers = (const uint8_t *)"Let the quest begin",
        .perslen = 19
    };

    const yespower_params_t *params = (time > 1553904000) ? &yespower_1_0 : &yespower_0_5;

    return yespower_tls((const uint8_t *)input, 80, params, (yespower_binary_t *)output);
}
