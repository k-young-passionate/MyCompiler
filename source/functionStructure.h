typedef enum
{ENUM_FUNC, ENUM_VAR} TYPE_E;

typedef enum
{ENUM_BLOCK, ENUM_BEND} Block_e;

typedef enum
{ENUM_SLIST, ENUM_STAT} Slist_e;

typedef enum
{ENUM_IF, ENUM_WHILE, ENUM_ASSIGN, ENUM_EEND} Stat_e;

typedef enum
{ENUM_FACT, ENUM_ADDITION} Expr_e;

typedef enum
{ENUM_NUM, ENUM_WORD} Fact_e;

struct FUNC {
	struct FUNC * next;
	struct PROG * root;
};

struct PROG {
	char * word;
	struct BLOCK * block;
};

struct BLOCK {
	Block_e be;
	struct SLIST * sl;
};

struct SLIST {
	Slist_e se;
	struct SLIST * sl;
	struct STAT * s;
};

struct STAT {
	Stat_e se;
	struct STAT_IF *statif;
	struct STAT_WHILE *statwhile;
	struct STAT_IF *statassign;
};

struct STAT_IF{
	struct COND *cond;
	struct BLOCK *ifblock;
	struct BLOCK *elseblock;
};

struct STAT_WHILE{
	struct COND *cond;
	struct BLOCK * block;
};

struct STAT_ASSIGN{
	char * word;
	char c;
	struct EXPR * expr;
};

struct COND {
	struct EXPR * e1;
	char c;
	struct EXPR * e2;
};

struct EXPR {
	Expr_e ee;
	struct EXPR * expr;
	struct FACT * f;
};

struct FACT {
	Fact_e fe;
	int num;
	char * word;
};

struct WORD{
	char *word;
};

struct NUM{
	int num;
};

