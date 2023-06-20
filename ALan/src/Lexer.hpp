#pragma once

#include <iostream>
#include <vector>
#include <string>

enum ETokenType
{
	TOKEN_UNDEFINED,    // €
	TOKEN_WHITESPACE,   // ' '

	TOKEN_SEMICOLON,    // ;
	TOKEN_COLON,        // :

	TOKEN_IDENTIFIER,   // main
	TOKEN_NUMBER,       // 187

	TOKEN_PAREN_RIGHT,  // (
	TOKEN_PAREN_LEFT,   // )

	TOKEN_CURLY_RIGHT,  // {
	TOKEN_CURLY_LEFT,   // }

	TOKEN_EQUAL,		// =
	TOKEN_PLUS,			// +
	TOKEN_MINUS,		// -
	TOKEN_SLASH,		// /
	TOKEN_STAR,			// *
	TOKEN_AMPERSAND,	// &
	TOKEN_VERTLINE,		// |
	TOKEN_LESSERTHAN,	// <
	TOKEN_GREATERTHAN,	// >
	TOKEN_QUESTION,		// ?

	TOKEN_VAR_TYPE,     // i32
	TOKEN_RETURN,       // return
	TOKEN_IF,           // if
	TOKEN_ELSE,         // else
	TOKEN_WHILE,        // while
	TOKEN_FOR,          // for
	TOKEN_BREAK,        // break
	TOKEN_CONTINUE,     // continue

	TOKEN_TRUE,         // true
	TOKEN_FALSE,        // false

	TOKEN_STRING,		// ""
};

struct CToken
{
	std::string data;
	ETokenType type;

	inline CToken(std::string _data, ETokenType _type)
	{
		this->data = _data;
		this->type = _type;
	};

	inline ~CToken()
	{
		return;
	};
};

class CLexer
{
private:
	const char *alphabet		= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	const char *digits			= "1234567890";
	const char *varTypes[12]	= { "i8", "i16", "i32", "i64", "u8", "u16", "u32", "u64", "f32", "f64", "bool", "str" };

	inline bool bCharInString(char token, const char *string)
	{
		for (int i = 0; i < strlen(string); ++i)
			if (token == string[i]) return true;
		return false;
	}
	
	inline void TokenIsVarType(CToken *token)
	{
		for (int i = 0; i < 12; ++i)
		{
			if (!strcmp(varTypes[i], token->data.c_str()))
			{
				std::cout << varTypes[i] << std::endl;
				token->type = TOKEN_VAR_TYPE;
				return;
			}
		}
	}

	inline ETokenType eGetTokenType(char token)
	{
		switch (token)
		{
		case '\n': return TOKEN_WHITESPACE;
		case '\r': return TOKEN_WHITESPACE;
		case '\t': return TOKEN_WHITESPACE;
		case '\0': return TOKEN_WHITESPACE;

		case ' ': return TOKEN_WHITESPACE;
		
		case ';': return TOKEN_SEMICOLON;
		case ':': return TOKEN_COLON;

		case '(': return TOKEN_PAREN_RIGHT;
		case ')': return TOKEN_PAREN_LEFT;

		case '{': return TOKEN_CURLY_RIGHT;
		case '}': return TOKEN_CURLY_LEFT;

		case '=': return TOKEN_EQUAL;
		case '+': return TOKEN_PLUS;
		case '-': return TOKEN_MINUS;
		case '/': return TOKEN_SLASH;
		case '*': return TOKEN_STAR;
		case '&': return TOKEN_AMPERSAND;
		case '|': return TOKEN_VERTLINE;
		case '<': return TOKEN_LESSERTHAN;
		case '>': return TOKEN_GREATERTHAN;
		case '?': return TOKEN_QUESTION;
		}

		if (bCharInString(token, alphabet)) return TOKEN_IDENTIFIER;
		if (bCharInString(token,   digits)) return TOKEN_NUMBER;

		return TOKEN_UNDEFINED;
	};

public:
	std::vector<CToken> tokens;

	inline CLexer(std::string code)
	{
		CToken fullToken = CToken(" ", TOKEN_WHITESPACE);
		
		for (size_t i = 0; i < code.size() + 1; ++i)
		{
			char character = code[i];

			CToken current = CToken(std::string({ character }), this->eGetTokenType(character));

			if (current.type == fullToken.type)
			{
				fullToken.data.push_back(*current.data.c_str());
			}
			else
			{
				if (fullToken.type == TOKEN_WHITESPACE)
					break;

				this->TokenIsVarType(&fullToken);

				const char *data = fullToken.data.c_str();

				if      (strcmp(data,   "return")) fullToken.type = TOKEN_RETURN;
				else if (strcmp(data,       "if")) fullToken.type = TOKEN_IF;
				else if (strcmp(data,     "else")) fullToken.type = TOKEN_ELSE;
				else if (strcmp(data,    "while")) fullToken.type = TOKEN_WHILE;
				else if (strcmp(data,      "for")) fullToken.type = TOKEN_FOR;
				else if (strcmp(data,    "break")) fullToken.type = TOKEN_BREAK;
				else if (strcmp(data, "continue")) fullToken.type = TOKEN_CONTINUE;
				else if (strcmp(data,     "true")) fullToken.type = TOKEN_TRUE;
				else if (strcmp(data,    "false")) fullToken.type = TOKEN_FALSE;

				this->tokens.push_back(fullToken);

				fullToken = CToken({ character }, this->eGetTokenType(character));
			}
		}
	};

	inline ~CLexer()
	{
		return;
	};
};