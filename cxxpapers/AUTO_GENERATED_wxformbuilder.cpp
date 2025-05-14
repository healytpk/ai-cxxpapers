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

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	btnLoadModel = new wxButton( this, wxID_ANY, _("Load Model"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( btnLoadModel, 0, wxALL, 5 );

	btnUnloadModel = new wxButton( this, wxID_ANY, _("Unload Model"), wxDefaultPosition, wxDefaultSize, 0 );
	btnUnloadModel->Enable( false );

	bSizer3->Add( btnUnloadModel, 0, wxALL, 5 );


	bSizer1->Add( bSizer3, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	btnLoadPapers = new wxButton( this, wxID_ANY, _("Load Papers"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( btnLoadPapers, 0, wxALL, 5 );

	btnUnloadPapers = new wxButton( this, wxID_ANY, _("Unload Papers"), wxDefaultPosition, wxDefaultSize, 0 );
	btnUnloadPapers->Enable( false );

	bSizer4->Add( btnUnloadPapers, 0, wxALL, 5 );


	bSizer1->Add( bSizer4, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );

	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Question to whittle down list of papers (must be a Yes/No question):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer1->Add( m_staticText1, 0, wxALL, 5 );

	txtBooleanQuestion = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,100 ), wxTE_MULTILINE );
	bSizer1->Add( txtBooleanQuestion, 0, wxALL|wxEXPAND, 5 );

	btnWhittleDownPapers = new wxButton( this, wxID_ANY, _("Next"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( btnWhittleDownPapers, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	lcPapers = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( -1,200 ), wxLC_REPORT );
	bSizer1->Add( lcPapers, 0, wxALL|wxEXPAND, 5 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, _("More detailed question to ask for each of the above papers:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer1->Add( m_staticText2, 0, wxALL, 5 );

	txtDetailedQuestion = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,80 ), wxTE_MULTILINE );
	bSizer1->Add( txtDetailedQuestion, 0, wxALL|wxEXPAND, 5 );

	btnAnalysePapers = new wxButton( this, wxID_ANY, _("Ask"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( btnAnalysePapers, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Responses:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer1->Add( m_staticText3, 0, wxALL, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	listPapers = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer2->Add( listPapers, 1, wxALL|wxEXPAND, 5 );

	txtDetailedAnswer = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer2->Add( txtDetailedAnswer, 1, wxALL|wxEXPAND, 5 );


	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( Dialog_Main__Auto_Base_Class::OnClose ) );
	btnLoadModel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Dialog_Main__Auto_Base_Class::btnLoadModel_OnButtonClick ), NULL, this );
	btnUnloadModel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Dialog_Main__Auto_Base_Class::btnUnloadModel_OnButtonClick ), NULL, this );
	btnLoadPapers->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Dialog_Main__Auto_Base_Class::btnLoadPapers_OnButtonClick ), NULL, this );
	btnWhittleDownPapers->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Dialog_Main__Auto_Base_Class::btnWhittleDownPapers_OnButtonClick ), NULL, this );
	btnAnalysePapers->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Dialog_Main__Auto_Base_Class::btnAnalysePapers_OnButtonClick ), NULL, this );
}

Dialog_Main__Auto_Base_Class::~Dialog_Main__Auto_Base_Class()
{
}
