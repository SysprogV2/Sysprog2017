#include "../includes/Automat.h"

Automat::Automat() {
	lexemReady = false;
    currentState = Syntax::STRT_Z;
    lastFinalState = Syntax::NULL_STATE;
    lexemLength = 0;
    back = 0;
    stack = new Stack();
    lexemLine = 0;
    lexemColumn = 0;
    syntax = new Syntax();

    gLine = 0;
    gCol = 0;
    tmpCol = 0;
}

Automat::~Automat() {
    delete stack;
    delete syntax;
}
/*
 * Automat consumes a character and then changes current state
 * according to the StateTable. When some valid lexem is found, it
 * saves important information about it such as position in input file,
 * lexem as char* and the last final state.
 * @return number of chars it looked ahead during execution
 */
int Automat::read(char currentChar) {
	updatePos(currentChar);
	if ( !lexemReady ) {
		currentState = syntax->getState(mapCharToSymbolName(currentChar), currentState);
		if (currentState != Syntax::OPNC_Z) stack->push(currentChar);
		lexemLength++;
		if (isFinal(currentState)) {
			lastFinalState = currentState;
			back = 0;
		} else {
			back++;
			if (currentState == Syntax::STRT_Z ) {
				lexemReady = true;
				stack->trim(back);						// delete last N (=back) characters
				lexemLength -= back; 					// adjust lexemLength
				updatePosition(back);
				return back;
			}
		}
	}
    return 0;
}



/*
 * only the following states are NOT final:
 * START_STATE, __<:__STATE, COMMENT_STATE
 * OPENING_COMMENT_STATE, END_OF_FILE_STATE
 */
bool Automat::isFinal(int someState) {
    return (someState != Syntax::STRT_Z &&
    		someState != Syntax::LCLN_Z &&
			someState != Syntax::COMM_Z &&
			someState != Syntax::OPNC_Z &&
			someState != Syntax::EOF_Z);
}

/*
 * resets the automata's state
 */
void Automat::reset() {
	lexemReady = false;
	stack->flush();
	lexemLength = 0;
	lastFinalState = Syntax::NULL_STATE;
}

/*
 * maps current character to a corresponding symbol in the StateTable
 * @return corresponding symbol for the StateTable
 */
int Automat::mapCharToSymbolName(char c) {
    if (isLetter(c))      		{  return Syntax::ANY_LETTER; }
    else if (isWspace(c)) 		{  return Syntax::WHITESPACE_SYMB; }
    else if (isDigit(c))  		{  return Syntax::ANY_DIGIT; }
    else if (c == '*')    		{  return Syntax::MULT_SYMB; }
    else if (c == ':')    		{  return Syntax::COLON_SYMB; }
    else if (c == '=')    		{  return Syntax::EQUALS_SYMB; }
    else if (c == '&')    		{  return Syntax::AND_SYMB; }
    else if (syntax->isPacked(c) > 0) {  return Syntax::REST_SYMB; }
    else if (c == '\0')   		{  return Syntax::EOF_SYMB; }
    else                  		{  return Syntax::PROH_SYMB; }
}

bool Automat::isLexemReady() {
	return lexemReady;
}

bool Automat::isDigit(char c) {
    return (c >= '0') && (c <= '9');
}

bool Automat::isLetter(char c) {
    return ((c >= 'a') && (c <= 'z')) ||
    		((c >= 'A') && (c <= 'Z'));
}

bool Automat::isWspace(char c) {
    return (c == '\n') || (c == ' ') ||  (c == '\t') || (c == '\r');
}

int Automat::getFinalState() {
	return lastFinalState;
}

const char* Automat::getLexem() {
	return stack->get();
}

int Automat::getLexemLength() {
	return lexemLength;
}

int Automat::getLine() {
	return gLine + 1;
}

int Automat::getColumn() {
	return gCol - lexemLength + 1;
}

void Automat::updatePos(char c) {
	gCol++;
	if (c == '\n') {
		gLine++;
		tmpCol = gCol;
		gCol = 0;
	}
}

void Automat::updatePosition(int back) {
	if (back > gCol) {
		gCol = tmpCol - back;
		gLine--;
	} else {
		gCol -= back;
	}
}




