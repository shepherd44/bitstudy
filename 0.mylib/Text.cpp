#include "StdAfx.h"
#include "Text.h"

CText::CText(void)
{
	m_CurrenTextpos.CurrenChar = 0;
	m_CurrenTextpos.CurrentLine = 0;
	// ù�� �߰� �ʿ�
	CHARS chsTemp;
	m_Lines.push_back(chsTemp);
	// ĳ�� �ʱ�ȭ
	m_CurrentCaret.x = 0;
	m_CurrentCaret.y = 0;
	
}

CText::~CText(void)
{
}

void CText::InitText(CDC* pDC)
{
	CFont * pFont = (CFont*)pDC->SelectStockObject( SYSTEM_FIXED_FONT );

	// ���� �ý��� ��Ʈ ���� ��������
	pDC->GetTextMetrics(&this->m_Textmetric);
	pDC->SelectObject(pFont);

}
POINT CText::GetCurrentCaretPos()
{
	return this->m_CurrentCaret;
}

void CText::SetCurrentCaretPos(CPoint pt)
{
	m_CurrentCaret.x = pt.x * m_Textmetric.tmAveCharWidth;
	m_CurrentCaret.y = pt.y * m_Textmetric.tmHeight;
}

void CText::InputReturn()
{
	CHARS chTemp;
	int len = GetCurrentLine()->m_chars.size();

	//���� ���ο����� �ε����� ���ϰ��
	if(m_CurrenTextpos.CurrenChar == len)
	{
		m_CurrenTextpos.CurrenChar = 0;
		m_CurrenTextpos.CurrentLine++;
		m_Lines.insert(m_Lines.begin() + m_CurrenTextpos.CurrentLine, chTemp);
	}
	// ���� ���ο����� �ε����� ������ ���� �ƴҰ��
	else
	{
		//���� ����
		UINT chsvi =this->m_CurrenTextpos.CurrentLine;
		CHARS& chsTemp = this->m_Lines.at(chsvi);
		//���� ���ο����� �ε���
		UINT chvi =this->m_CurrenTextpos.CurrenChar;
		// ���๮�� ������ �߶��ֱ�
		
		for(; chvi<chsTemp.m_chars.size();)
		{
			chTemp.m_chars.push_back(chsTemp.m_chars.at(chvi));
			chsTemp.m_chars.erase(chsTemp.m_chars.begin()+chvi);
		}
		this->m_CurrenTextpos.CurrentLine++;
		this->m_Lines.insert(this->m_Lines.begin() + m_CurrenTextpos.CurrentLine, chTemp);
		// ���๮�� �Է� �� �������� ù��° ���ڸ� ����Ű��
		this->m_CurrenTextpos.CurrenChar = 0;
	}
	SetCurrentCaretPos(CPoint(m_CurrenTextpos.CurrenChar, m_CurrenTextpos.CurrentLine));
	
}
void CText::InputChar(TCHAR ch)
{
	m_Lines.at(m_CurrenTextpos.CurrentLine).m_chars.insert(GetCurrentLine()->m_chars.begin() + m_CurrenTextpos.CurrenChar,ch);
	m_CurrenTextpos.CurrenChar++;
	SetCurrentCaretPos(CPoint(m_CurrenTextpos.CurrenChar, m_CurrenTextpos.CurrentLine));
}

void CText::InputChar(UINT ch)
{
	TCHAR charr[2] = {ch};
	int len = wcslen(charr);
	for(int i=0; i< wcslen(charr); i++)
	{
		m_Lines.at(m_CurrenTextpos.CurrentLine).m_chars.insert(GetCurrentLine()->m_chars.begin() + m_CurrenTextpos.CurrenChar, charr[i]);
	}
	m_CurrenTextpos.CurrenChar++;
	SetCurrentCaretPos(CPoint(m_CurrenTextpos.CurrenChar, m_CurrenTextpos.CurrentLine));
}


void CText::InputArrow(UINT VK)
{
	int len = 0;
	switch( VK ) 
	{
	case VK_UP:
		{
			if(m_CurrenTextpos.CurrentLine > 0)
			{
				m_CurrenTextpos.CurrentLine--;
				// Ŀ���� ���� �̵��� ��� �� ������ �Ʒ� ���κ��� ª�� �� ����. �� ��� ó��
				len = GetCurrentLine()->m_chars.size();
				if(m_CurrenTextpos.CurrenChar > len)
					m_CurrenTextpos.CurrenChar = len;
			}
		}
		break;
	case VK_DOWN:
		{
			len = GetLines().size()-1;
			if(m_CurrenTextpos.CurrentLine < len)
			{
				m_CurrenTextpos.CurrentLine++;
				len = GetCurrentLine()->m_chars.size();
				if(m_CurrenTextpos.CurrenChar > len)
					m_CurrenTextpos.CurrenChar = len;
			}
		}
		break;
	case VK_LEFT:
		{
			if(m_CurrenTextpos.CurrenChar > 0)
				m_CurrenTextpos.CurrenChar--;
		}
		break;
	case VK_RIGHT:
		{
			len = GetCurrentLine()->m_chars.size();
			if(m_CurrenTextpos.CurrenChar < len)
				m_CurrenTextpos.CurrenChar++;
		}
		break;
	}
	SetCurrentCaretPos(CPoint(m_CurrenTextpos.CurrenChar, m_CurrenTextpos.CurrentLine));
}

void CText::AllTextOut(CDC* pDC)
{
	std::vector<CHARS>& vcs = m_Lines;
	
	for(UINT i=0;i<vcs.size();i++)
	{
		std::vector<TCHAR>& vc = vcs.at(i).m_chars;
		for(int j=0; j<vc.size(); j++)
		{
			pDC->TextOutW(m_Textmetric.tmAveCharWidth*j,m_Textmetric.tmHeight*i, (LPCTSTR)&vc.at(j), 1);
		}
	}

}
void CText::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
		//POSITION p =  m_list.GetHeadPosition(); 	
		//for( int i = 0; i< m_list.GetCount(); i++) 
		//{	
		//	// ar <<  m_list.GetNext( p );   // << �����ε� : �⺻ Ÿ��, CString
		//	CString str = m_list.GetNext(p); 
		//	str.AppendChar(L"\r\n");
		//	ar.WriteString( str );
		//}

		CString str;
		TCHAR chre[] = {TEXT("\r\n")};
		std::vector<CHARS>& vcs = this->m_Lines;
		for(UINT i=0;i<vcs.size();i++)
		{
			std::vector<TCHAR>& vc = vcs.at(i).m_chars;
			for(int j=0; j<vc.size(); j++)
			{
				str.AppendChar(vc.at(j));
			}
			str.AppendFormat(TEXT("\r\n"));
			ar.WriteString(str);
			str.Format(TEXT(""));
		}
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}

}

TCHAR* CText::TextToTCHAR()
{
	TCHAR ch;
	return NULL;
}
CString CText::TextToCString()
{
	CString str;
	return str;
}