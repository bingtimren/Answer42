void show_w_confirmation(void);
void hide_w_confirmation(void);

typedef void(* ConfirmationReceived)(bool confirmed);

void confirmation_ask(const char* prompt, ConfirmationReceived callback);
