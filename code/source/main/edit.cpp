#include <zed/app.h>
#include <zed/app/input.h>

#include "game.h"

void edit_vignette() {

if ( app_input.get.key_y.held ) game.draw.vignette.roundness  = max( -1.0, ( game.draw.vignette.roundness  - 0.01 ) );
if ( app_input.get.key_u.held ) game.draw.vignette.roundness  = min(  1.0, ( game.draw.vignette.roundness  + 0.01 ) );
if ( app_input.get.key_h.held ) game.draw.vignette.radius_min = max(  0.0, ( game.draw.vignette.radius_min - 0.01 ) );
if ( app_input.get.key_j.held ) game.draw.vignette.radius_min = min(  1.0, ( game.draw.vignette.radius_min + 0.01 ) );
if ( app_input.get.key_n.held ) game.draw.vignette.radius_max = max(  0.0, ( game.draw.vignette.radius_max - 0.01 ) );
if ( app_input.get.key_m.held ) game.draw.vignette.radius_max = min(  1.0, ( game.draw.vignette.radius_max + 0.01 ) );

}
