///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "AUTO_GENERATED_wxformbuilder.h"

///////////////////////////////////////////////////////////////////////////

Dialog_Main__Auto_Base_Class::Dialog_Main__Auto_Base_Class( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Question to whittle down list of papers (must be a Yes/No question):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer1->Add( m_staticText1, 0, wxALL, 5 );

	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,100 ), wxTE_MULTILINE );
	bSizer1->Add( m_textCtrl1, 0, wxALL|wxEXPAND, 5 );

	m_button1 = new wxButton( this, wxID_ANY, _("Next"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_button1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_listCtrl1 = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( -1,200 ), wxLC_REPORT );
	bSizer1->Add( m_listCtrl1, 0, wxALL|wxEXPAND, 5 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, _("More detailed question to ask for each of the above papers:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer1->Add( m_staticText2, 0, wxALL, 5 );

	m_textCtrl2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,80 ), wxTE_MULTILINE );
	bSizer1->Add( m_textCtrl2, 0, wxALL|wxEXPAND, 5 );

	m_button2 = new wxButton( this, wxID_ANY, _("Ask"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_button2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Responses:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer1->Add( m_staticText3, 0, wxALL, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	m_listBox1 = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer2->Add( m_listBox1, 1, wxALL|wxEXPAND, 5 );

	m_textCtrl3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer2->Add( m_textCtrl3, 1, wxALL|wxEXPAND, 5 );


	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( Dialog_Main__Auto_Base_Class::OnClose ) );
}

Dialog_Main__Auto_Base_Class::~Dialog_Main__Auto_Base_Class()
{
}
