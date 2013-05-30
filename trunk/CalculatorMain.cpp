/***************************************************************
 * Name:      CalculatorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Lupin Long (longxia102@gmail.com)
 * Created:   2013-04-12
 * Copyright: Lupin Long (http://www.cnzui.com)
 * License:
 **************************************************************/

#include "CalculatorMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(CalculatorDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(CalculatorDialog)
const long CalculatorDialog::ID_TEXTRESULT = wxNewId();
const long CalculatorDialog::ID_RADIODEC = wxNewId();
const long CalculatorDialog::ID_RADIOHEX = wxNewId();
const long CalculatorDialog::ID_RADIOOCT = wxNewId();
const long CalculatorDialog::ID_BTNCLEAR = wxNewId();
const long CalculatorDialog::ID_BTNDIVID = wxNewId();
const long CalculatorDialog::ID_BTNMULTIPLY = wxNewId();
const long CalculatorDialog::ID_BTNSEVEN = wxNewId();
const long CalculatorDialog::ID_BTNEIGHT = wxNewId();
const long CalculatorDialog::ID_BTNNINE = wxNewId();
const long CalculatorDialog::ID_BTNFOUR = wxNewId();
const long CalculatorDialog::ID_BTNFIVE = wxNewId();
const long CalculatorDialog::ID_BTNSIX = wxNewId();
const long CalculatorDialog::ID_BTNONE = wxNewId();
const long CalculatorDialog::ID_BTNTWO = wxNewId();
const long CalculatorDialog::ID_BTNTHREE = wxNewId();
const long CalculatorDialog::ID_BTNZERO = wxNewId();
const long CalculatorDialog::ID_BTNDOT = wxNewId();
const long CalculatorDialog::ID_BTNMiNUS = wxNewId();
const long CalculatorDialog::ID_BTNPLUS = wxNewId();
const long CalculatorDialog::ID_BTNEQUAL = wxNewId();
const long CalculatorDialog::ID_CONTROLPANEL = wxNewId();
const long CalculatorDialog::ID_MESSAGEDIALOG1 = wxNewId();
//*)

wxString transformresult="";
void OctTransform(int num)
{
    if(num<8)
    {
        transformresult.Printf("%d%s",num%8,transformresult);
    }
    else
    {
        transformresult.Printf("%d%s",num%8,transformresult);
        OctTransform(num/8);
    }
}

void HexTransform(int num)
{
    if(num<16)
    {
        transformresult.Printf("%d%s",num%8,transformresult);
    }
    else
    {
        int modresult=num%16;
        char ch[1];
        switch(modresult)
        {
        case 10:
            ch[0]='A';
            break;
        case 11:
            ch[0]='B';
            break;
        case 12:
            ch[0]='C';
            break;
        case 13:
            ch[0]='D';
            break;
        case 14:
            ch[0]='E';
            break;
        case 15:
            ch[0]='F';
            break;
        default:
            itoa(modresult,ch,10);
            break;
        }
        transformresult.Printf("%c%s",ch[0],transformresult);
        HexTransform(num/16);
    }
}

BEGIN_EVENT_TABLE(CalculatorDialog,wxDialog)
    //(*EventTable(CalculatorDialog)
    //*)
END_EVENT_TABLE()

CalculatorDialog::CalculatorDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(CalculatorDialog)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxGridBagSizer* GridBagSizer1;
    wxBoxSizer* BoxSizer2;
    wxGridSizer* GridSizer1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxBoxSizer* BoxSizer3;

    Create(parent, wxID_ANY, _("Calculator"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    txtResult = new wxTextCtrl(this, ID_TEXTRESULT, _("0."), wxDefaultPosition, wxSize(-1,30), wxTE_READONLY|wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTRESULT"));
    txtResult->SetBackgroundColour(wxColour(176,176,176));
    wxFont txtResultFont(14,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    txtResult->SetFont(txtResultFont);
    BoxSizer2->Add(txtResult, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Options"));
    rdoDec = new wxRadioButton(this, ID_RADIODEC, _("Dec"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIODEC"));
    rdoDec->SetValue(true);
    StaticBoxSizer1->Add(rdoDec, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    rdoHex = new wxRadioButton(this, ID_RADIOHEX, _("Hex"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOHEX"));
    StaticBoxSizer1->Add(rdoHex, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    rdoOct = new wxRadioButton(this, ID_RADIOOCT, _("Oct"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOOCT"));
    StaticBoxSizer1->Add(rdoOct, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(StaticBoxSizer1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    plControlPanel = new wxPanel(this, ID_CONTROLPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_CONTROLPANEL"));
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    GridBagSizer1 = new wxGridBagSizer(0, 0);
    GridSizer1 = new wxGridSizer(0, 3, 0, 0);
    btnClear = new wxButton(plControlPanel, ID_BTNCLEAR, _("C"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNCLEAR"));
    btnClear->SetForegroundColour(wxColour(255,0,0));
    GridSizer1->Add(btnClear, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnDivid = new wxButton(plControlPanel, ID_BTNDIVID, _("/"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNDIVID"));
    GridSizer1->Add(btnDivid, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnMultiply = new wxButton(plControlPanel, ID_BTNMULTIPLY, _("*"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNMULTIPLY"));
    GridSizer1->Add(btnMultiply, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnSeven = new wxButton(plControlPanel, ID_BTNSEVEN, _("7"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNSEVEN"));
    btnSeven->SetForegroundColour(wxColour(0,0,255));
    GridSizer1->Add(btnSeven, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnEight = new wxButton(plControlPanel, ID_BTNEIGHT, _("8"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNEIGHT"));
    btnEight->SetForegroundColour(wxColour(0,0,255));
    GridSizer1->Add(btnEight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnNine = new wxButton(plControlPanel, ID_BTNNINE, _("9"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNNINE"));
    btnNine->SetForegroundColour(wxColour(0,0,255));
    GridSizer1->Add(btnNine, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnFour = new wxButton(plControlPanel, ID_BTNFOUR, _("4"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNFOUR"));
    btnFour->SetForegroundColour(wxColour(0,0,255));
    GridSizer1->Add(btnFour, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnFive = new wxButton(plControlPanel, ID_BTNFIVE, _("5"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNFIVE"));
    btnFive->SetForegroundColour(wxColour(0,0,255));
    GridSizer1->Add(btnFive, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnSix = new wxButton(plControlPanel, ID_BTNSIX, _("6"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNSIX"));
    btnSix->SetForegroundColour(wxColour(0,0,255));
    GridSizer1->Add(btnSix, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnOne = new wxButton(plControlPanel, ID_BTNONE, _("1"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNONE"));
    btnOne->SetForegroundColour(wxColour(0,0,255));
    GridSizer1->Add(btnOne, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnTwo = new wxButton(plControlPanel, ID_BTNTWO, _("2"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNTWO"));
    btnTwo->SetForegroundColour(wxColour(0,0,255));
    GridSizer1->Add(btnTwo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnThree = new wxButton(plControlPanel, ID_BTNTHREE, _("3"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNTHREE"));
    btnThree->SetForegroundColour(wxColour(0,0,255));
    GridSizer1->Add(btnThree, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    GridBagSizer1->Add(GridSizer1, wxGBPosition(0, 0), wxDefaultSpan, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    btnZero = new wxButton(plControlPanel, ID_BTNZERO, _("0"), wxDefaultPosition, wxSize(84,40), 0, wxDefaultValidator, _T("ID_BTNZERO"));
    btnZero->SetForegroundColour(wxColour(0,0,255));
    BoxSizer5->Add(btnZero, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnDot = new wxButton(plControlPanel, ID_BTNDOT, _("."), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNDOT"));
    btnDot->SetForegroundColour(wxColour(0,0,255));
    BoxSizer5->Add(btnDot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    GridBagSizer1->Add(BoxSizer5, wxGBPosition(1, 0), wxDefaultSpan, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3->Add(GridBagSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer4 = new wxBoxSizer(wxVERTICAL);
    btnMinus = new wxButton(plControlPanel, ID_BTNMiNUS, _("-"), wxDefaultPosition, wxSize(40,40), 0, wxDefaultValidator, _T("ID_BTNMiNUS"));
    BoxSizer4->Add(btnMinus, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnPlus = new wxButton(plControlPanel, ID_BTNPLUS, _("+"), wxDefaultPosition, wxSize(40,84), 0, wxDefaultValidator, _T("ID_BTNPLUS"));
    BoxSizer4->Add(btnPlus, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    btnEqual = new wxButton(plControlPanel, ID_BTNEQUAL, _("="), wxDefaultPosition, wxSize(40,84), 0, wxDefaultValidator, _T("ID_BTNEQUAL"));
    BoxSizer4->Add(btnEqual, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    BoxSizer3->Add(BoxSizer4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    plControlPanel->SetSizer(BoxSizer3);
    BoxSizer3->Fit(plControlPanel);
    BoxSizer3->SetSizeHints(plControlPanel);
    BoxSizer1->Add(plControlPanel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    MessageDialog1 = new wxMessageDialog(this, wxEmptyString, _("Message"), wxOK|wxCANCEL, wxDefaultPosition);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);
    Center();

    Connect(ID_RADIODEC,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&CalculatorDialog::OnrdoDecSelect);
    Connect(ID_RADIOHEX,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&CalculatorDialog::OnrdoHexSelect);
    Connect(ID_RADIOOCT,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&CalculatorDialog::OnrdoOctSelect);
    Connect(ID_BTNCLEAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnClearClick);
    Connect(ID_BTNDIVID,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnDividClick);
    Connect(ID_BTNMULTIPLY,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnMultiplyClick);
    Connect(ID_BTNSEVEN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnSevenClick);
    Connect(ID_BTNEIGHT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnEightClick);
    Connect(ID_BTNNINE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnNineClick);
    Connect(ID_BTNFOUR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnFourClick);
    Connect(ID_BTNFIVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnFiveClick);
    Connect(ID_BTNSIX,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnSixClick);
    Connect(ID_BTNONE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnOneClick);
    Connect(ID_BTNTWO,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnTwoClick);
    Connect(ID_BTNTHREE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnThreeClick);
    Connect(ID_BTNZERO,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnZeroClick);
    Connect(ID_BTNDOT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnDotClick);
    Connect(ID_BTNMiNUS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnMinusClick);
    Connect(ID_BTNPLUS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnPlusClick);
    Connect(ID_BTNEQUAL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorDialog::OnbtnEqualClick);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&CalculatorDialog::OnInit);
    //*)
}

CalculatorDialog::~CalculatorDialog()
{
    //(*Destroy(CalculatorDialog)
    //*)
}

void CalculatorDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void CalculatorDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void CalculatorDialog::OnInit(wxInitDialogEvent& event)
{
    Init();
}

void CalculatorDialog::OnbtnClearClick(wxCommandEvent& event)
{
    txtResult->Clear();
    SetOperator(NONE);
}

void CalculatorDialog::OnbtnDividClick(wxCommandEvent& event)
{
    SetOperator(DIVID);
}

void CalculatorDialog::OnbtnMultiplyClick(wxCommandEvent& event)
{
    SetOperator(MULTIPLY);
}

void CalculatorDialog::OnbtnMinusClick(wxCommandEvent& event)
{
    SetOperator(MINUS);
}

void CalculatorDialog::OnbtnPlusClick(wxCommandEvent& event)
{
    SetOperator(PLUS);
}

void CalculatorDialog::OnbtnEqualClick(wxCommandEvent& event)
{
    //Start to calculate
    Run();
}

void CalculatorDialog::OnbtnSevenClick(wxCommandEvent& event)
{
    Input("7");
}

void CalculatorDialog::OnbtnEightClick(wxCommandEvent& event)
{
    Input("8");
}

void CalculatorDialog::OnbtnNineClick(wxCommandEvent& event)
{
    Input("9");
}

void CalculatorDialog::OnbtnFourClick(wxCommandEvent& event)
{
    Input("4");
}

void CalculatorDialog::OnbtnFiveClick(wxCommandEvent& event)
{
    Input("5");
}

void CalculatorDialog::OnbtnSixClick(wxCommandEvent& event)
{
    Input("6");
}

void CalculatorDialog::OnbtnOneClick(wxCommandEvent& event)
{
    Input("1");
}

void CalculatorDialog::OnbtnTwoClick(wxCommandEvent& event)
{
    Input("2");
}

void CalculatorDialog::OnbtnThreeClick(wxCommandEvent& event)
{
    Input("3");
}

void CalculatorDialog::OnbtnZeroClick(wxCommandEvent& event)
{
    Input("0");
}

void CalculatorDialog::OnbtnDotClick(wxCommandEvent& event)
{
    Input(".");
}

void CalculatorDialog::OnrdoDecSelect(wxCommandEvent& event)
{
    if(this->m_nCurNum!=0)
    {
        txtResult->SetValue(GetResultTxt(this->m_nCurNum));
    }
    else
    {
        txtResult->SetValue(GetResultTxt(this->m_nPrevNum));
    }
    SwitchControlPad(true);
}

void CalculatorDialog::OnrdoHexSelect(wxCommandEvent& event)
{
    double num=0;
    if(this->m_nCurNum!=0)
    {
        num=this->m_nCurNum;
    }
    else
    {
        num=this->m_nPrevNum;
    }

    if(num<0)
    {
        rdoDec->SetValue(true);
        event.Skip(false);
        return;
    }
    transformresult="";
    HexTransform(num);
    txtResult->SetValue(transformresult);
    SwitchControlPad(false);
}

void CalculatorDialog::OnrdoOctSelect(wxCommandEvent& event)
{
    double num=0;
    if(this->m_nCurNum!=0)
    {
        num=this->m_nCurNum;
    }
    else
    {
        num=this->m_nPrevNum;
    }
    if(num<0)
    {
        rdoDec->SetValue(true);
        event.Skip(false);
        return;
    }
    transformresult="";
    OctTransform(num);
    txtResult->SetValue(transformresult);
    SwitchControlPad(false);
}
