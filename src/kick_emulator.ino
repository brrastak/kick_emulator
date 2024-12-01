#include "bsp.hpp"
#include "config.hpp"
#include "counter.hpp"


void setup() {
  
}


enum class Mode {
    manual,
    single,
    automatic,
};

enum class MotorState {
    stopped,
    moving_forth,
    moving_back,
    waiting,
};

hal::Counter counter;
bsp::Bsp& board = bsp::Bsp::take();
Mode mode = Mode::manual;
MotorState state = MotorState::stopped;


// Move forth and then back
Mode proceed_single(MotorState& state);
// Move forth and then back repeatedly
void proceed_automatic(MotorState& state);
// Control physical motor movement
void control_motor(bsp::Bsp& board, MotorState state);


void loop() {


    delay(1);
    board.update();

    // Mode control
    if (board.mode_button().was_released()) {
        if (board.mode_button().get_press_duration() < 500) {
            mode = Mode::single;
        }
        else {
            mode = Mode::automatic;
        }
    }
    if (board.forth_button().was_pressed() || board.back_button().was_pressed()) {
        mode = Mode::manual;
    }

    // Manual mode
    if (mode == Mode::manual) {
        if (board.forth_button().is_pressed()) {
            state = MotorState::moving_forth;
        }
        else {
            if (board.back_button().is_pressed()) {
                state = MotorState::moving_back;
            }
            else {
                state = MotorState::stopped;
            }
        }
    }

    // Single mode
    if (mode == Mode::single) {
        mode = proceed_single(state);
    }

    // Automatic mode
    if (mode == Mode::automatic) {
        proceed_automatic(state);
    }

    // Actuators
    control_motor(board, state);
}


Mode proceed_single(MotorState& state) {
    static hal::Counter counter;

    switch (state)
    {
    case MotorState::stopped:
        state = MotorState::moving_forth;
        counter.reset();
        break;

    case MotorState::moving_forth:
        if (counter.is_timeout_passed(config::moving_time)) {
            state = MotorState::moving_back;
        }
        break;

    case MotorState::moving_back:
        if (counter.is_timeout_passed(config::moving_time)) {
            state = MotorState::stopped;
            mode = Mode::manual;
        }
        break;
    }
}

void proceed_automatic(MotorState& state) {
    static hal::Counter counter;

    switch (state)
    {
    case MotorState::stopped:
        state = MotorState::moving_forth;
        counter.reset();
        break;

    case MotorState::moving_forth:
        if (counter.is_timeout_passed(config::moving_time)) {
            state = MotorState::moving_back;
        }
        break;

    case MotorState::moving_back:
        if (counter.is_timeout_passed(config::moving_time)) {
            state = MotorState::waiting;
        }
        break;

    case MotorState::waiting:
        if (counter.is_timeout_passed(config::waiting_time)) {
            state = MotorState::moving_forth;
        }
        break;
    }
}

void control_motor(bsp::Bsp& board, MotorState state) {
    switch (state)
    {
    case MotorState::stopped:
        board.stop_motor();
        board.led1().reset();
        board.led2().reset();
        break;

    case MotorState::moving_forth:
        board.move_forth();
        board.led1().set();
        board.led2().reset();
        break;

    case MotorState::moving_back:
        board.move_back();
        board.led1().reset();
        board.led2().set();
        break;

    case MotorState::waiting:
        board.stop_motor();
        board.led1().set();
        board.led2().set();
        break;
    }
}
