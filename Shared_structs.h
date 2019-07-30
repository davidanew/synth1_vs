#pragma once


struct Note_on_struct {
	uint8_t note_number {0}	;
	uint8_t velocity {0};
	uint32_t get_frequecy()
	{
		return note_number;
	}
};

struct Controller_change_struct {
	uint8_t controller_number {0};
	uint8_t controller_data {0};
};









