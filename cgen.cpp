#include "globals.h"
#include "util.h"
#include "cgen.h"

static int tempNo = 0;
static int labelNo = 0;

static char* newTemp() {
    static char buf[10];
    sprintf(buf, "t%d", ++tempNo);
    return copyString(buf);
}

static char* newLabel() {
    static char buf[10];
    sprintf(buf, "L%d", ++labelNo);
    return copyString(buf);
}

static void emit(const char* op, const char* arg1, const char* arg2, const char* res) {
    fprintf(code, "(%s, %s, %s, %s)\n", op, arg1 ? arg1 : "-", arg2 ? arg2 : "-", res ? res : "-");
}

static void emitLabel(const char* label) {
    fprintf(code, "%s:\n", label);
}

static char* cGen(TreeNode* tree);

static char* cGen(TreeNode* tree) {
    if (tree == NULL) return NULL;
    
    char* s = NULL;
    char* p1 = NULL;
    char* p2 = NULL;
    char* p3 = NULL;
    
    if (tree->nodekind == StmtK) {
        switch (tree->kind.stmt) {
            case IfK:
                p1 = cGen(tree->child[0]); // cond
                p2 = newLabel(); // else/end
                p3 = newLabel(); // end
                emit("jfalse", p1, "-", p2);
                cGen(tree->child[1]); // then
                if (tree->child[2] != NULL) { // else exists
                    emit("jmp", "-", "-", p3);
                    emitLabel(p2);
                    cGen(tree->child[2]); // else
                    emitLabel(p3);
                } else {
                    emitLabel(p2);
                }
                break;
            case WhileK:
                p1 = newLabel(); // start
                p2 = newLabel(); // end
                emitLabel(p1);
                p3 = cGen(tree->child[0]); // cond
                emit("jfalse", p3, "-", p2);
                cGen(tree->child[1]); // body
                emit("jmp", "-", "-", p1);
                emitLabel(p2);
                break;
            case ForK:
                // child[0]: init (AssignK or IncK or ...)
                cGen(tree->child[0]);
                p1 = newLabel(); // start
                p2 = newLabel(); // end
                emitLabel(p1);
                p3 = cGen(tree->child[1]); // cond
                emit("jfalse", p3, "-", p2);
                cGen(tree->child[3]); // body
                cGen(tree->child[2]); // inc
                emit("jmp", "-", "-", p1);
                emitLabel(p2);
                break;
            case RepeatK:
                p1 = newLabel(); // start
                emitLabel(p1);
                cGen(tree->child[0]); // body
                p2 = cGen(tree->child[1]); // until cond
                emit("jfalse", p2, "-", p1); // Repeat until true? "repeat ... until exp". Usually until exp is true, stop. So if exp is false, repeat.
                break;
            case AssignK:
                p1 = cGen(tree->child[0]);
                emit("assign", p1, "-", tree->attr.name);
                break;
            case PlusEqK:
                p1 = cGen(tree->child[0]); // exp
                emit("add", tree->attr.name, p1, tree->attr.name);
                break;
            case MinusEqK:
                p1 = cGen(tree->child[0]); // exp
                emit("sub", tree->attr.name, p1, tree->attr.name);
                break;
            case IncK: // ++ID as statement
                emit("add", tree->attr.name, "1", tree->attr.name);
                break;
            case DecK: // --ID as statement
                emit("sub", tree->attr.name, "1", tree->attr.name);
                break;
            case ReadK:
                emit("read", "-", "-", tree->attr.name);
                break;
            case WriteK:
                p1 = cGen(tree->child[0]);
                emit("write", p1, "-", "-");
                break;
            default:
                break;
        }
    } else if (tree->nodekind == ExpK) {
        switch (tree->kind.exp) {
            case IdK:
                s = tree->attr.name;
                break;
            case ConstK:
                s = (char*)malloc(20);
                sprintf(s, "%d", tree->attr.val);
                break;
            case OpK:
                if (tree->attr.op == INC || tree->attr.op == DEC) {
                    // Prefix ++/-- on child[0] (IdK)
                    if (tree->child[0] != NULL) {
                        char* id = tree->child[0]->attr.name;
                        if (id != NULL) {
                            if (tree->attr.op == INC)
                                emit("add", id, "1", id);
                            else
                                emit("sub", id, "1", id);
                            s = id; // Result is the new value
                        }
                    }
                } else {
                    p1 = cGen(tree->child[0]);
                    p2 = cGen(tree->child[1]);
                    s = newTemp();
                    char* opName = NULL;
                    switch(tree->attr.op) {
                        case PLUS: opName = "add"; break;
                        case MINUS: opName = "sub"; break;
                        case TIMES: opName = "mul"; break;
                        case OVER: opName = "div"; break;
                        case REMAIN: opName = "mod"; break;
                        case POWER: opName = "pow"; break;
                        case LT: opName = "lt"; break;
                        case GT: opName = "gt"; break;
                        case EQ: opName = "eq"; break;
                        case NEQ: opName = "neq"; break;
                        case LTE: opName = "le"; break;
                        case GTE: opName = "ge"; break;
                        default: opName = "op"; break;
                    }
                    emit(opName, p1, p2, s);
                }
                break;
            default:
                break;
        }
    }
    
    // Process siblings
    cGen(tree->sibling);
    
    return s;
}

void codeGen(TreeNode *syntaxTree, const char *codefile) {
    char *s = (char *)malloc(strlen(codefile) + 7);
    strcpy(s, codefile);
    code = fopen(s, "w");
    if (code == NULL) {
        return;
    }
    tempNo = 0;
    labelNo = 0;
    cGen(syntaxTree);
    fclose(code);
}
