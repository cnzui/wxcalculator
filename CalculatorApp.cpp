/***************************************************************
 * Name:      CalculatorApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Lupin Long (longxia102@gmail.com)
 * Created:   2013-04-12
 * Copyright: Lupin Long (http://www.cnzui.com)
 * License:
 **************************************************************/

#include "CalculatorApp.h"

//(*AppHeaders
#include "CalculatorMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(CalculatorApp);

bool CalculatorApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	CalculatorDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
