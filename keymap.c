#include QMK_KEYBOARD_H

#define LAYOUT_ortho_4x5( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, k23, \
    k30, k31, k32, k33,  \
    k40, k41, k42, k43  \
) { \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, k33 }, \
    { k40, k41, k42, k43 }  \
}

// Layers.
#define DEFAULT_LAYER 0
#define PHPSTORM_LAYER 1
#define SLACK_LAYER 2
#define ZOOM_LAYER 3
#define SWITCH_LAYER 4

#define XXXXXXX KC_NO
#define _______ KC_TRNS

enum custom_keycodes {
	CK_SWITCH = OSL( SWITCH_LAYER ),
	CK_PSTORM = TO( PHPSTORM_LAYER ),
	CK_SLACK = TO( SLACK_LAYER ),
	CK_ZOOM = TO( ZOOM_LAYER ),
	CK_DEFAULT = TO( DEFAULT_LAYER ),
	CK_ZOOM_SHARE = LGUI( LSFT( KC_S ) ),
	CK_ZOOM_MUTE = LGUI( LSFT( KC_A ) ),
	CK_ZOOM_VIDEO = LGUI( LSFT( KC_V ) ),
	CK_ZOOM_INVITE = LGUI( KC_I ),
	CK_ZOOM_CHAT = LGUI( LSFT( KC_H ) ),
	CK_ZOOM_RECORD = LGUI( LSFT( KC_R ) ),
	CK_ZOOM_LEAVE = LGUI( KC_W ),
	SLACK_ZOOM = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[ DEFAULT_LAYER ] = LAYOUT_ortho_4x5(
		KC_MPLY, KC_VOLD, KC_VOLU, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, CK_SWITCH
	),
	[ PHPSTORM_LAYER ] = LAYOUT_ortho_4x5(
		LGUI( KC_F8 ), XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX,       XXXXXXX, XXXXXXX, CK_SWITCH
	),
	[ SLACK_LAYER ] = LAYOUT_ortho_4x5(
		SLACK_ZOOM, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX, CK_SWITCH
	),
	[ ZOOM_LAYER ] = LAYOUT_ortho_4x5(
		CK_ZOOM_SHARE,  CK_ZOOM_MUTE, CK_ZOOM_VIDEO, CK_ZOOM_RECORD, 
		CK_ZOOM_INVITE, CK_ZOOM_CHAT, CK_ZOOM_LEAVE, XXXXXXX,
		XXXXXXX,        XXXXXXX,      XXXXXXX,       XXXXXXX,
		XXXXXXX,        XXXXXXX,      XXXXXXX,       XXXXXXX,
		XXXXXXX,        XXXXXXX,      XXXXXXX,       CK_SWITCH
	),
	[ SWITCH_LAYER ] = LAYOUT_ortho_4x5(
		CK_PSTORM, CK_SLACK, CK_ZOOM, XXXXXXX, 
		XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX,
		XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX,
		XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX,
		XXXXXXX,   XXXXXXX,  RESET, CK_DEFAULT
	)
};

bool process_record_user( uint16_t keycode, keyrecord_t *record ) {
	switch ( keycode ) {
		case SLACK_ZOOM:
			if ( record->event.pressed ) {
				// Open Zoom with Alfred.
				SEND_STRING( SS_DOWN( X_LGUI ) SS_TAP( X_SPACE ) SS_UP( X_LGUI ) );
				_delay_ms( 250 );
				SEND_STRING( SS_TAP( X_Z ) SS_TAP( X_O ) SS_TAP( X_O ) SS_TAP( X_M ) SS_TAP( X_ENTER ) );
				
				// Wait for open.
				_delay_ms( 5000 );

				// Jump back to slack and send /zoom.
				SEND_STRING( SS_DOWN( X_LGUI ) SS_TAP( X_SPACE ) SS_UP( X_LGUI ) );
				_delay_ms( 250 );
				SEND_STRING( SS_TAP( X_S ) SS_TAP( X_L ) SS_TAP( X_A ) SS_TAP( X_C ) SS_TAP( X_K ) SS_TAP( X_ENTER ) );
				_delay_ms( 250 );
				SEND_STRING( SS_TAP( X_SLASH ) SS_TAP( X_Z ) SS_TAP( X_O ) SS_TAP( X_O ) SS_TAP( X_M ) SS_TAP( X_SPACE ) SS_TAP( X_ENTER ) );
				
				// Wait for zoom link to appear then tab to it and open it.
				_delay_ms( 1500 );
				SEND_STRING( SS_DOWN( X_LSHIFT ) SS_TAP( X_TAB ) SS_TAP( X_TAB ) SS_TAP( X_TAB ) SS_TAP( X_TAB ) SS_TAP( X_TAB ) SS_TAP( X_TAB ) SS_TAP( X_TAB ) SS_TAP( X_TAB ) SS_UP( X_LSHIFT ) SS_TAP( X_ENTER ) );
				return false;
			}
			break;
	}
	return true;
}
