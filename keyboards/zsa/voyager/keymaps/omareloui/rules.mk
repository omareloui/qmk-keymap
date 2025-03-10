COMBO_ENABLE = yes
REPEAT_KEY_ENABLE = yes

UNICODE_ENABLE = no
UCIS_ENABLE = no
UNICODEMAP_ENABLE = no
UNICODE_COMMON = yes

EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = no

AUTOCORRECT_ENABLE ?= yes
LAYER_LOCK_ENABLE ?= yes
RGB_MATRIX_CUSTOM_USER ?= yes

CUSTOM_SHIFT_KEYS_ENABLE ?= yes
ifeq ($(strip $(CUSTOM_SHIFT_KEYS_ENABLE)), yes)
	OPT_DEFS += -DCUSTOM_SHIFT_KEYS_ENABLE
	SRC += features/custom_shift_keys.c
endif

SENTENCE_CASE_ENABLE ?= yes
ifeq ($(strip $(SENTENCE_CASE_ENABLE)), yes)
	OPT_DEFS += -DSENTENCE_CASE_ENABLE
	SRC += features/sentence_case.c
endif

SELECT_WORD_ENABLE ?= yes
ifeq ($(strip $(SELECT_WORD_ENABLE)), yes)
	OPT_DEFS += -DSELECT_WORD_ENABLE
	SRC += features/select_word.c
endif

ORBITAL_MOUSE_ENABLE ?= yes
ifeq ($(strip $(ORBITAL_MOUSE_ENABLE)), yes)
	MOUSE_ENABLE = yes
	OPT_DEFS += -DORBITAL_MOUSE_ENABLE
	SRC += features/orbital_mouse.c
endif
