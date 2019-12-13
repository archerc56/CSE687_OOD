#pragma once

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:

	int test1 = 0;
	int test2 = 0;
	int test3 = 0;
	int test4 = 0;
	int w = 4;
	int h = 1;
	int x = 0;
	int y = 0;
	int incremental = 50;
	wxButton**btn;
	wxButton* generate_list;
	wxListBox* list_of_test;
	int* f = nullptr;
	bool firstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);
	void GenerateXML(wxCommandEvent& evt);

	// Handles events
	wxDECLARE_EVENT_TABLE();


};

