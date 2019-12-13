#include "cMain.h"
#include <wx/textfile.h>

// Macros for button event handling 
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

// Base class doesnt have a parent, thus nullptr is provided
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "TestRequest", wxPoint(30, 30), wxSize(600,400))
{

	list_of_test = new wxListBox(this, wxID_ANY, wxPoint(140, 10), wxSize(150, 300));
	btn = new wxButton*[w * h];
	int start_value = 10;
	for (int x = 0; x < w; x++)
	{
		wxString test_name = "Test";
		test_name += std::to_string(x + 1);
		if (x == 0)
			btn[x] = new wxButton(this, 10000+x, test_name, wxPoint(10, start_value), wxSize(120, 40));
		else
			btn[x] = new wxButton(this, 10000+x, test_name, wxPoint(10, (start_value += incremental)), wxSize(120, 40));

		btn[x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
	}
	generate_list = new wxButton(this, wxID_ANY, "Generate XML", wxPoint(10, 300), wxSize(120, 40));
	generate_list->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::GenerateXML, this);

}
	


cMain::~cMain()
{
	delete[] btn;
}

void cMain::GenerateXML(wxCommandEvent& evt)
{

	remove("test.xml");
	wxTextFile file("test.xml");
	file.Create("test.xml");
	file.Open("test.xml");
	file.AddLine("< ? xml version = \"1.0\" ? >");
	file.AddLine("<xs:element name = \"test_name\" type = \"xs:string\" / >");

	if (test1 != 0)
		file.AddLine("<test_name>test1</test_name>");
	if (test2 != 0)
		file.AddLine("<test_name>test2</test_name>");
	if (test3 !=0)
		file.AddLine("<test_name>test3</test_name>");
	if (test4 !=0 )
		file.AddLine("<test_name>test4</test_name>");


	file.Write();
	file.Close();
	evt.Skip();
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	
	wxString test_name = "";
	int id = evt.GetId();
	id = id - 10000;
	if (id == 0)
	{
		if (test1 != 0)
		{
			evt.Skip();
		}
		else
		{
			test_name = "Test1";
			test1 = 1;
			list_of_test->AppendString(test_name);
		}
	}
	if (id == 1)
	{
		if (test2 != 0)
		{
			evt.Skip();
		}
		else
		{
			test_name = "Test2";
			test2 = 1;
			list_of_test->AppendString(test_name);
		}
	}
	if (id == 2)
	{
		if (test3 != 0)
		{
			evt.Skip();
		}
		else
		{
			test_name = "Test3";
			test3= 1;
			list_of_test->AppendString(test_name);
		}
	}
	if (id == 3)
	{
		if (test4!= 0)
		{
			evt.Skip();
		}
		else
		{
			test_name = "Test4";
			test4= 1;
			list_of_test->AppendString(test_name);
		}
	}
	evt.Skip(); // Event has finish

}