#include "cApp.h"
#include "cMain.h"

// Launcher
// Generates main for us. 
wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}

cApp::~cApp()
{

}

bool cApp::OnInit()
{
	m_frame1 = new cMain();
	m_frame1->Show();
	return true;
}

