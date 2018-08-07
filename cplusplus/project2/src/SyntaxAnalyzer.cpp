#include "SyntaxAnalyzer.h"

    SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer* lex, VariableTable* vt) {
        lexic = lex;
        variableTable = vt;
    }


    Operation* SyntaxAnalyzer::analyse() {
        try {
            analyse(0, &root);
            Operation* result = root.oper1;
            root.oper1 = 0;
            return result;
        } catch (AnalyzeException& s) {
            cout << '\n' << s.what() << endl;
        }
        root.freeMemory();
        return root.oper1;
    }

    void SyntaxAnalyzer::analyse(int isbracket, OneOperation *parent) {
        Operation *o1 = analyseOperation(parent);
        int opernum = 1;
        while (true) {
            TokenProtoype& token = nextToken(2, 0);
            if (lexic->eoi()) {
                break;
            }
            if (token.value == ")") {
                if (isbracket) {
                    return;
                } else {
                    string mes = "Illegal close bracket ')'. Token: " + o1->asstring();
                    throw AnalyzeException(mes.c_str(), lexic->currentToken(), lexic->eoi(), root.oper1);
                }
            }
            TwoOperation *op2 = ((TwoOperation*) getOpertion(token, 2));
            // сохранить операцию в цепочке, на случай ошибки, что бы освободить память
            op2->setOperation2(o1);
            parent->setOperation(op2);
            Operation *o2 = analyseOperation(op2);
            // теперь op2->oper2, где o1 уже не нужна
            op2->setOperation2(o2);
            if (opernum == 1 || op2->priority <= o1->priority) {
                op2->setOperation(o1);
                o1 = op2;
            } else {
                TwoOperation* memop = (TwoOperation *) o1;
                op2->setOperation(memop->oper2);
                memop->setOperation2(op2);
                parent->setOperation(o1);
            }
            opernum++;
        }
        if (isbracket) {
            string mes = "There is no close bracket ')'. Token: " + o1->asstring();
            throw AnalyzeException(mes.c_str(), lexic->currentToken(), lexic->eoi(), root.oper1);
        }
    }

    Operation* SyntaxAnalyzer::getOpertion(TokenProtoype& token, int n) {
        int index = (n == 1 ? token.ioper1 : token.ioper2);
        switch (index) {
            case ONE_MINUS_INDEX:
                return new OneMinus(index);
            case ONE_PLUS_INDEX:
                return new OnePlus(index);
            case OBRACKET_INDEX:
                return new Bracket(index);
            case TWO_MINUS_INDEX:
                return new TwoMinus(index);
            case TWO_PLUS_INDEX:
                return new TwoPlus(index);
            case TWO_MULTI_INDEX:
                return new TwoMulti(index);
            case TWO_DIVIDE_INDEX:
                return new TwoDivide(index);
            case TWO_MORE_INDEX:
                return new TwoMore(index);
            case TWO_EQU_INDEX:
                return new TwoEqu(index);
            case TWO_LESS_INDEX:
                return new TwoLess(index);
            case TWO_AND_INDEX:
                return new TwoAnd(index);
            case TWO_OR_INDEX:
                return new TwoOr(index);
            case ONE_NOT_INDEX:
                return new OneNot(index);
            case INTEGER_INDEX:
                return new IntegerOperand(index);
            case FIELD_INDEX:
                return new Field();
            case VARIABLE_INDEX:
                return new Variable();
            case CBRACKET_INDEX:
                return new Operation(CBRACKET_INDEX, CBRACKET_PRIORITY);
            case FUNCTION_INDEX:
                if (0 == token.value.compare("sqrt")) {
                    return new SqrtFunction();
                }
                if (0 == token.value.compare("avg")) {
                    return new AvgFunction();
                }
                if (0 == token.value.compare("min")) {
                    return new MinFunction();
                }
                if (0 == token.value.compare("max")) {
                    return new MaxFunction();
                }
                throw AnalyzeException("Unexpected Function: ", token.value);
            default:
                throw AnalyzeException("Unexpected Operation index: ", index);
        }
    }

    Operation* SyntaxAnalyzer::analyseOperation(OneOperation *parent) {
        TokenProtoype& token = nextToken(1, parent);
        if (lexic->eoi()) {
            throw AnalyzeException("Unexpected end of tokens", lexic->currentToken(), lexic->eoi(), root.oper1);
        }
        int index = token.ioper1;
        Operation* result = getOpertion(token, 1);
        if (parent) {
            parent->setOperation(result);
        }
        if (index == OBRACKET_INDEX) {
            analyse(1, (OneOperation*) result);
        } else if (index == INTEGER_INDEX) {
            ((IntegerOperand*) result)->parse(token.value);
        } else if (index == DOUBLE_INDEX) {
            ((DoubleOperand*) result)->parse(token.value);
        } else if (index == FUNCTION_INDEX) {
            OneOperation oper1 = ((Function*) result)->bufferoper;
            analyse(1, &oper1);
            ((Function*) result)->oper = oper1.oper1;
            oper1.oper1 = 0;
        } else if (index == VARIABLE_INDEX) {
            Field* f = variableTable->getField(token.value);
            if (f) {
                if (f->aggrkey) {
                    string mes = "Key aggregation field in formula: " + token.value;
                    throw AnalyzeException(mes.c_str(), lexic->currentToken(), lexic->eoi(), root.oper1);
                }
                ((Variable*)result)->name = token.value;
                ((Variable*)result)->oper = f;
            }
            else {
                throw AnalyzeException("Invalid field name", lexic->currentToken(), lexic->eoi(), root.oper1);
            }
        } else {
            analyseOperation((OneOperation*) result);
        }
        return result;
    }

    TokenProtoype& SyntaxAnalyzer::nextToken(int operNumber, OneOperation *parent) {
        TokenProtoype& token = lexic->nextToken();
        if (lexic->eoi()) {
            return token;
        }
        int index = operNumber == 1 ? token.ioper1 : token.ioper2;
        if (!index) {
            throw AnalyzeException("Unexpected token", lexic->currentToken(), lexic->eoi(), root.oper1);
        }
        if (parent && !parent->validNext(index)) {
            throw AnalyzeException("Invalid token sequence", lexic->currentToken(), lexic->eoi(), root.oper1);
        }
        return token;
    }
