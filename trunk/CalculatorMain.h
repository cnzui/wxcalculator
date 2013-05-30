/***************************************************************
 * Name:      CalculatorMain.h
 * Purpose:   Defines Application Frame
 * Author:    Lupin Long (longxia102@gmail.com)
 * Created:   2013-04-12
 * Copyright: Lupin Long (http://www.cnzui.com)
 * License:
 **************************************************************/

#ifndef CALCULATORMAIN_H
#define CALCULATORMAIN_H

//(*Headers(CalculatorDialog)
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/msgdlg.h>
#include <wx/radiobut.h>
#include <wx/panel.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#define NONE        -1
#define PLUS        0
#define MINUS       1
#define MULTIPLY    2
#define DIVID       3
#define EQUAL       4

class CalculatorDialog: public wxDialog
{
    public:

        CalculatorDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~CalculatorDialog();

    private:

        //(*Handlers(CalculatorDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnInit(wxInitDialogEvent& event);
        void OnbtnClearClick(wxCommandEvent& event);
        void OnbtnMultiplyClick(wxCommandEvent& event);
        void OnbtnMinusClick(wxCommandEvent& event);
        void OnbtnPlusClick(wxCommandEvent& event);
        void OnbtnEqualClick(wxCommandEvent& event);
        void OnbtnSevenClick(wxCommandEvent& event);
        void OnbtnEightClick(wxCommandEvent& event);
        void OnbtnNineClick(wxCommandEvent& event);
        void OnbtnFourClick(wxCommandEvent& event);
        void OnbtnFiveClick(wxCommandEvent& event);
        void OnbtnSixClick(wxCommandEvent& event);
        void OnbtnOneClick(wxCommandEvent& event);
        void OnbtnZeroClick(wxCommandEvent& event);
        void OnbtnDotClick(wxCommandEvent& event);
        void OnbtnTwoClick(wxCommandEvent& event);
        void OnbtnThreeClick(wxCommandEvent& event);
        void OnbtnDividClick(wxCommandEvent& event);
        void OnrdoDecSelect(wxCommandEvent& event);
        void OnrdoHexSelect(wxCommandEvent& event);
        void OnrdoOctSelect(wxCommandEvent& event);
        //*)

        //(*Identifiers(CalculatorDialog)
        static const long ID_TEXTRESULT;
        static const long ID_RADIODEC;
        static const long ID_RADIOHEX;
        static const long ID_RADIOOCT;
        static const long ID_BTNCLEAR;
        static const long ID_BTNDIVID;
        static const long ID_BTNMULTIPLY;
        static const long ID_BTNSEVEN;
        static const long ID_BTNEIGHT;
        static const long ID_BTNNINE;
        static const long ID_BTNFOUR;
        static const long ID_BTNFIVE;
        static const long ID_BTNSIX;
        static const long ID_BTNONE;
        static const long ID_BTNTWO;
        static const long ID_BTNTHREE;
        static const long ID_BTNZERO;
        static const long ID_BTNDOT;
        static const long ID_BTNMiNUS;
        static const long ID_BTNPLUS;
        static const long ID_BTNEQUAL;
        static const long ID_CONTROLPANEL;
        static const long ID_MESSAGEDIALOG1;
        //*)

        //(*Declarations(CalculatorDialog)
        wxButton* btnFour;
        wxButton* btnNine;
        wxTextCtrl* txtResult;
        wxButton* btnZero;
        wxButton* btnEqual;
        wxButton* btnPlus;
        wxButton* btnSix;
        wxButton* btnOne;
        wxButton* btnThree;
        wxButton* btnClear;
        wxButton* btnDivid;
        wxButton* btnMinus;
        wxRadioButton* rdoHex;
        wxBoxSizer* BoxSizer1;
        wxButton* btnDot;
        wxRadioButton* rdoOct;
        wxButton* btnFive;
        wxRadioButton* rdoDec;
        wxMessageDialog* MessageDialog1;
        wxPanel* plControlPanel;
        wxButton* btnSeven;
        wxButton* btnEight;
        wxButton* btnMultiply;
        wxButton* btnTwo;
        //*)

    private:
        int m_nCurOperator; //+,-,*,/
        double m_nPrevNum;
        double m_nCurNum;
        bool m_bIsFloat;
        bool m_bIsFirstIn;
    private:
        void Init()
        {
            this->txtResult->SetValue("0.");
            this->m_nCurNum=0;
            this->m_nPrevNum=0;
            this->m_bIsFloat=false;
            this->m_bIsFirstIn=true;
            this->m_nCurOperator=NONE;
        }
        void SwitchControlPad(bool enable)
        {
            wxWindowList controls = this->plControlPanel->GetChildren();

             wxWindowList::iterator iter;
             for (iter = controls.begin(); iter != controls.end(); ++iter)
             {
                    wxWindow *button = *iter;
                    if(button!=NULL)  button->Enable(enable);
             }
        }

        static wxString GetResultTxt(double result)
        {
            wxString resultstr=wxString::Format("%.13f",result);
            //delete the fractional when total length max than 14
            while(resultstr.Len()>14 && resultstr.Find('.')!=(int)resultstr.Len()-1)
            {
                resultstr=resultstr.Left(resultstr.Len()-1);
            }
            //delete 0 behind the string
            while(resultstr.Find('0',true)==(int)resultstr.Len()-1)
            {
                if(resultstr.Len()>1)
                {
                    resultstr=resultstr.Left(resultstr.Len()-1);
                }
                else
                {
                    break;
                }
            }

            //while result is max then 14,you can use the scientific notation

            return resultstr;
        }

        void Input(wxString num)
        {
            wxString curnumstr=GetResultTxt(this->m_nCurNum);
            //avoid max than 14 bit
            if(curnumstr.Len()==14)
            {
                return;
            }

            if(curnumstr=="0.")
            {
                if(num==".")
                {
                    this->m_bIsFloat=true;
                }
                else
                {
                    if(!m_bIsFloat)
                    {
                        this->txtResult->SetValue(wxString::Format("%s.",num));
                    }
                    else
                    {
                        this->txtResult->AppendText(wxString::Format("%s",num));
                    }
                }
            }
            else
            {
                if(curnumstr.Find('.')==(int)curnumstr.Len()-1 && !m_bIsFloat)
                {
                    if(num==".")
                    {
                        this->m_bIsFloat=true;
                    }
                    else
                    {
                        wxString numstr=curnumstr.Left(curnumstr.Len()-1);
                        this->txtResult->SetValue(wxString::Format("%s%s.",numstr,num));
                    }
                }
                else
                {
                    if(num!=".")
                    {
                        this->txtResult->AppendText(wxString::Format("%s",num));
                    }
                }
            }

            this->m_nCurNum=wxAtof(this->txtResult->GetValue());
        }

        void SetOperator(int p)
        {
            if(p==NONE)
            {
                Init();
            }
            else
            {
                if(m_bIsFirstIn)
                {
                    this->m_bIsFirstIn=false;
                    this->m_nPrevNum=wxAtof(this->txtResult->GetValue());
                    this->m_nCurOperator=p;
                }
                else
                {
                    this->m_nCurNum=wxAtof(this->txtResult->GetValue());
                    Run();
                }

                //reset
                m_bIsFloat=false;
                this->m_nCurNum=0;
            }
        }

        void Run()
        {
            double result=0;

            if(m_bIsFirstIn)
            {
                result=wxAtof(this->txtResult->GetValue());
            }
            else
            {
                switch(this->m_nCurOperator)
                {
                case PLUS:
                    result=this->m_nPrevNum + this->m_nCurNum;
                    break;
                case MINUS:
                    result=this->m_nPrevNum - this->m_nCurNum;
                    break;
                case MULTIPLY:
                    result=this->m_nPrevNum * this->m_nCurNum;
                    break;
                case DIVID:
                    if(this->m_nCurNum!=0)
                    {
                        result=this->m_nPrevNum / this->m_nCurNum;
                    }
                    else
                    {
                        wxMessageBox("Can not divided by zero!");
                    }
                    break;
                case NONE:
                default:
                    result= this->m_nPrevNum;
                    break;
                }
            }

            this->m_nPrevNum=result;
            this->txtResult->SetValue(GetResultTxt(result));

            if(result<0)
            {
                rdoDec->SetValue(true);
                rdoHex->Enable(false);
                rdoOct->Enable(false);
            }
            else
            {
                rdoHex->Enable(true);
                rdoOct->Enable(true);
            }

            //reset
            this->m_bIsFirstIn=true;
            this->m_bIsFloat=false;
            this->m_nCurNum=0;
        }
        DECLARE_EVENT_TABLE()
};

#endif // CALCULATORMAIN_H
