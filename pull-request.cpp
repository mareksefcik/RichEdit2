void Tab1::OnAdd()
{
	UpdateData(TRUE);					// update member		
	m_listBox.AddString(m_EditString);
	//UpdateData(FALSE);				// update gui
	int x = 1;
	x++;
	++x;
}

void Tab1::OnButton1()
{
	UpdateData(TRUE); // gui > member
	m_sText1.Format(_T("Check1 : %d, Check2 : %d"), m_bCheck1, m_bCheck2);
	UpdateData(FALSE); // member > gui
}

void Tab1::OnGet()
{
	int index;
	CString strText;
	index = m_listBox.GetCurSel();
	m_listBox.GetText(index, strText);
	MessageBox(strText);
}

void Tab1::OnRemove()
{
	int index;
	CString strText;
	index = m_listBox.GetCurSel();
	m_listBox.DeleteString(index);
}

void Tab1::OnSelChangeLB()
{
	int index;
	CString strText;
	index = m_listBox.GetCurSel();
	m_listBox.GetText(index, strText);
	//MessageBox(strText);
}