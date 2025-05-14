#include "GUI_Dialog_Main.hpp"

#include <cassert>                                   // assert
#include <cstddef>                                   // size_t
#include <cstring>                                   // strcmp, strstr
#include <string>                                    // string
#include <vector>                                    // vector
#include <thread>                                    // jthread
#include <wx/app.h>                                  // wxApp
#include <wx/msgdlg.h>                               // wxMessageBox

#include "GUI_Dialog_Waiting.hpp"
#include "ai.hpp"
#include "paperman.hpp"

Dialog_Main *g_p_dlgmain = nullptr;

AImanager g_aimanager;
PaperManager g_paperman("./paperfiles/papers/");

class App_CxxPapers : public wxApp {
public:

    bool OnInit(void) override
    {
        wxThread::SetConcurrency(2u);

        RecreateGUI();

        return true;
    }

	int OnExit(void) override
	{
		return 0;
	}

	void RecreateGUI(void)
	{
		//wxMessageBox( wxT("Recreating GUI") );

		wxWindow *const topwindow = this->GetTopWindow();

		if ( topwindow )
		{
			this->SetTopWindow(nullptr);
			topwindow->Destroy();
		}

        g_p_dlgmain = new Dialog_Main(nullptr);

        g_p_dlgmain->Show();   /* Just let this throw if it fails */
	}
};

//DECLARE_APP(App_CxxPapers);  -  Not needed

IMPLEMENT_APP(App_CxxPapers);  // This creates the "main" function

Dialog_Main::Dialog_Main(wxWindow *const parent) : Dialog_Main__Auto_Base_Class(parent)
{
    /* Nothing to do in here */
}

void Dialog_Main::OnClose(wxCloseEvent& event)
{
    this->Destroy();
}

void Dialog_Main::btnLoadModel_OnButtonClick(wxCommandEvent&)
{
    Dialog_Waiting &dlg = *new Dialog_Waiting(nullptr, "Loading the artificial intelligence model. . .");
    dlg.m_gauge->SetRange(100u);
    dlg.m_gauge->Hide();

    std::atomic_bool model_is_loaded{false};

    std::jthread mythread([&dlg,&model_is_loaded]
      {
          model_is_loaded = g_aimanager.Init();
          dlg.CallAfter( &Dialog_Waiting::CallAfter_Destroy );
      });

    dlg.ShowModal();

    this->btnLoadModel  ->Enable( ! model_is_loaded );
    this->btnUnloadModel->Enable(   model_is_loaded );
}

void Dialog_Main::btnLoadPapers_OnButtonClick(wxCommandEvent&)
{
    Dialog_Waiting &dlg = *new Dialog_Waiting(nullptr, "Loading the thousands of C++ papers. . .");
    dlg.m_gauge->SetRange(100u);
    dlg.m_gauge->Hide();

    std::atomic_bool is_loaded{false};

    std::jthread mythread([&dlg,&is_loaded]
      {
          try
          {
              g_paperman.LoadAllTokensFromAllPapers();
              is_loaded = true;
          }
          catch(...) {}

          dlg.CallAfter( &Dialog_Waiting::CallAfter_Destroy );
      });

    dlg.ShowModal();

    this->btnLoadPapers  ->Enable( ! is_loaded );
    this->btnUnloadPapers->Enable(   is_loaded );
}

void Dialog_Main::btnUnloadModel_OnButtonClick(wxCommandEvent&)
{
    g_aimanager.Reset();
    this->btnLoadModel  ->Enable( true  );
    this->btnUnloadModel->Enable( false );
}

