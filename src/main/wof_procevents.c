// wof_procevents.c -- the proc events by name, a debug table that no function reads
//
// An object of data alone, with no text: the original assembler's stale fill before 0x80057170 closes
// the object before it, and its data runs on without fill to the table's end at 0x80057800. It lies
// in .data between the puzzle object's data and wof_opening's, so it is linked between them, among
// the string, proc, obj and memory-stack objects; the proc object is a candidate for its owner, which
// would put this data at the start of that object's .data, but no function of it reads the table.
// Each name is its own char array: the strings lie in .data, where GCC puts no string literal.
//
// Entry n of procEventNames reads "<NAME> n" for every n from 0 to 52: the original names of the
// event numbers, which wof.h defines from these strings (PRC_EVENT_INIT is 8). Each array is named
// for the event it spells.

#include "wof.h"

static char prcEventNullName[] = "PRC_EVENT_NULL 0";
static char prcEventNextPlayerName[] = "PRC_EVENT_NEXT_PLAYER 1";
static char prcEventWheelStoppedName[] = "PRC_EVENT_WHEEL_STOPPED 2";
static char prcEventDoneSpiningName[] = "PRC_EVENT_DONE_SPINING 3";
static char prcEventWheelAlmostStoppedName[] = "PRC_EVENT_WHEEL_ALMOST_STOPPED 4";
static char prcEventDoneSelectingName[] = "PRC_EVENT_DONE_SELECTING 5";
static char prcEventDoneRevealingName[] = "PRC_EVENT_DONE_REVEALING 6";
static char prcEventWheelLongSpinName[] = "PRC_EVENT_WHEEL_LONG_SPIN 7";
static char prcEventInitName[] = "PRC_EVENT_INIT 8";
static char prcEventDoneVowelName[] = "PRC_EVENT_DONE_VOWEL 9";
static char prcEventDoneSolveName[] = "PRC_EVENT_DONE_SOLVE 10";
static char prcEventStatusWakeupName[] = "PRC_EVENT_STATUS_WAKEUP 11";
static char prcEventSpinSelectedName[] = "PRC_EVENT_SPIN_SELECTED 12";
static char prcEventSvowelSelectedName[] = "PRC_EVENT_SVOWEL_SELECTED 13";
static char prcEventSolveSelectedName[] = "PRC_EVENT_SOLVE_SELECTED 14";
static char prcEventNextRoundName[] = "PRC_EVENT_NEXT_ROUND 15";
static char prcEventVideoDoneName[] = "PRC_EVENT_VIDEO_DONE 16";
static char prcEventCursorRightName[] = "PRC_EVENT_CURSOR_RIGHT 17";
static char prcEventCursorLeftName[] = "PRC_EVENT_CURSOR_LEFT 18";
static char prcEventHighlightAllName[] = "PRC_EVENT_HIGHLIGHT_ALL 19";
static char prcEventClearGuessedName[] = "PRC_EVENT_CLEAR_GUESSED 20";
static char prcEventRoundOverName[] = "PRC_EVENT_ROUND_OVER 21";
static char prcSelectionChangedName[] = "PRC_SELECTION_CHANGED 22";
static char prcEventComputerSelectedName[] = "PRC_EVENT_COMPUTER_SELECTED 23";
static char prcEventComputerDoneName[] = "PRC_EVENT_COMPUTER_DONE 24";
static char prcEventSolveNextName[] = "PRC_EVENT_SOLVE_NEXT 25";
static char prcEventSolveChangedName[] = "PRC_EVENT_SOLVE_CHANGED 26";
static char prcEventComputerChangedName[] = "PRC_EVENT_COMPUTER_CHANGED 27";
static char prcEventComputerSelectName[] = "PRC_EVENT_COMPUTER_SELECT 28";
static char prcEventPlayerSpunName[] = "PRC_EVENT_PLAYER_SPUN 29";
static char prcEventGameTimeoutName[] = "PRC_EVENT_GAME_TIMEOUT 30";
static char prcEventDoneSpeedupName[] = "PRC_EVENT_DONE_SPEEDUP 31";
static char prcEventDoneFinalSpinName[] = "PRC_EVENT_DONE_FINAL_SPIN 32";
static char prcEventSolveTimeoutName[] = "PRC_EVENT_SOLVE_TIMEOUT 33";
static char prcEventDemoTimeoutName[] = "PRC_EVENT_DEMO_TIMEOUT 34";
static char prcEventDemoResetName[] = "PRC_EVENT_DEMO_RESET 35";
static char prcEventStartPressedName[] = "PRC_EVENT_START_PRESSED 36";
static char prcEventUseFreeSpinName[] = "PRC_EVENT_USE_FREE_SPIN 37";
static char prcEventFreeSpinUsedName[] = "PRC_EVENT_FREE_SPIN_USED 38";
static char prcEventStartRoundName[] = "PRC_EVENT_START_ROUND 39";
static char prcEventStartFirstRoundName[] = "PRC_EVENT_START_FIRST_ROUND 40";
static char prcEventNextSoundName[] = "PRC_EVENT_NEXT_SOUND 41";
static char prcEventBonusRoundName[] = "PRC_EVENT_BONUS_ROUND 42";
static char prcEventResetStartTimeName[] = "PRC_EVENT_RESET_START_TIME 43";
static char prcEventDoneSayingName[] = "PRC_EVENT_DONE_SAYING 44";
static char prcEventDoneCampathName[] = "PRC_EVENT_DONE_CAMPATH 45";
static char prcEventGameOverName[] = "PRC_EVENT_GAME_OVER 46";
static char prcEventStopFlashingPuzzleName[] = "PRC_EVENT_STOP_FLASHING_PUZZLE 47";
static char prcEventFreeTimeoutName[] = "PRC_EVENT_FREE_TIMEOUT 48";
static char prcEventVannaStoppedName[] = "PRC_EVENT_VANNA_STOPPED 49";
static char prcEventUpExcitementName[] = "PRC_EVENT_UP_EXCITEMENT 50";
static char prcEventNotEnoughName[] = "PRC_EVENT_NOT_ENOUGH 51";
static char prcEventNotEnough2Name[] = "PRC_EVENT_NOT_ENOUGH2 52";
char *procEventNames[53] = {
    prcEventNullName, prcEventNextPlayerName, prcEventWheelStoppedName, prcEventDoneSpiningName, prcEventWheelAlmostStoppedName, prcEventDoneSelectingName, prcEventDoneRevealingName, prcEventWheelLongSpinName,
    prcEventInitName, prcEventDoneVowelName, prcEventDoneSolveName, prcEventStatusWakeupName, prcEventSpinSelectedName, prcEventSvowelSelectedName, prcEventSolveSelectedName, prcEventNextRoundName,
    prcEventVideoDoneName, prcEventCursorRightName, prcEventCursorLeftName, prcEventHighlightAllName, prcEventClearGuessedName, prcEventRoundOverName, prcSelectionChangedName, prcEventComputerSelectedName,
    prcEventComputerDoneName, prcEventSolveNextName, prcEventSolveChangedName, prcEventComputerChangedName, prcEventComputerSelectName, prcEventPlayerSpunName, prcEventGameTimeoutName, prcEventDoneSpeedupName,
    prcEventDoneFinalSpinName, prcEventSolveTimeoutName, prcEventDemoTimeoutName, prcEventDemoResetName, prcEventStartPressedName, prcEventUseFreeSpinName, prcEventFreeSpinUsedName, prcEventStartRoundName,
    prcEventStartFirstRoundName, prcEventNextSoundName, prcEventBonusRoundName, prcEventResetStartTimeName, prcEventDoneSayingName, prcEventDoneCampathName, prcEventGameOverName, prcEventStopFlashingPuzzleName,
    prcEventFreeTimeoutName, prcEventVannaStoppedName, prcEventUpExcitementName, prcEventNotEnoughName, prcEventNotEnough2Name
};
