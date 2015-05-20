#pragma once
#include <list>
#include <vector>

typedef struct Chars{
	std::vector<TCHAR> m_chars;
}CHARS;

typedef struct TextPos{
	UINT CurrentLine;	// ���� ��
	UINT CurrenChar;	// ���� �ٿ����� �ε���
}TEXTPOS;

class CText : public CObject
{
private:
	
	//��ü �ؽ�Ʈ
	std::vector<CHARS> m_Lines;

	TEXTMETRIC m_Textmetric;
	CPoint m_CurrentCaret;
	TEXTPOS m_CurrenTextpos;


public:
	CText(void);
	~CText(void);

	void InitText(CDC*);
	POINT GetCurrentCaretPos();
	void SetCurrentCaretPos(CPoint);
	void InputReturn();
	void InputChar(TCHAR);
	void InputChar(UINT);
	void InputArrow(UINT);
	void AllTextOut(CDC*);
	TEXTPOS GetCurrentTextpos()		{ return m_CurrenTextpos; }
	TEXTMETRIC* GetPTextmetric()	{ return &m_Textmetric; }
	std::vector<CHARS>& GetLines()	{ return m_Lines; }
	CHARS* GetCurrentLine()			{ return &m_Lines.at(m_CurrenTextpos.CurrentLine); }
	int GetCurrentLineSize()		{ return m_Lines.at(m_CurrenTextpos.CurrentLine).m_chars.size();}
	TCHAR* TextToTCHAR();
	CString TextToCString();
	void Serialize(CArchive &ar);
};