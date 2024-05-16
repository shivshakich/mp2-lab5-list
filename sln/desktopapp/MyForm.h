#pragma once

#include <msclr/marshal_cppstd.h>
#include <string>
#include <vector>
#include "../../include/tpolynom.h"

static std::vector<TPolynom> vec;

namespace CppWinForm1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;




	protected:
		
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(77, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"ПОЛИНОМ";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(107, 13);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(612, 22);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(770, 10);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"ДОБАВИТЬ";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(107, 41);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(200, 22);
			this->textBox2->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 47);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(85, 16);
			this->label2->TabIndex = 4;
			this->label2->Text = L"ДЕЙСТВИЕ";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(313, 41);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(200, 22);
			this->textBox3->TabIndex = 5;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(519, 41);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(200, 22);
			this->textBox4->TabIndex = 6;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(771, 40);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(99, 23);
			this->button2->TabIndex = 7;
			this->button2->Text = L"ВЫБРАТЬ";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->BackgroundColor = System::Drawing::Color::White;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->Column1,
					this->Column2
			});
			this->dataGridView1->Location = System::Drawing::Point(16, 70);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(854, 471);
			this->dataGridView1->TabIndex = 8;
			// 
			// Column1
			// 
			this->Column1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->Column1->HeaderText = L"№";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Width = 50;
			// 
			// Column2
			// 
			this->Column2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->Column2->HeaderText = L"POLYNOMIAL";
			this->Column2->MinimumWidth = 6;
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			this->Column2->Width = 121;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->ClientSize = System::Drawing::Size(882, 553);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	std::string in = msclr::interop::marshal_as< std::string >(textBox1->Text);
	
	try {
		TPolynom pol(in);
		vec.push_back(pol);

		int ind = dataGridView1->Rows->Add();
		dataGridView1->Rows[ind]->Cells[0]->Value = vec.size();

		// ">:-U"
		String^ s = gcnew String(pol.ToString().c_str());		
		dataGridView1->Rows[ind]->Cells[1]->Value = s;
	}
	catch (...) {

		textBox1->Text = "НЕПРАВИЛЬНАЯ ЗАПИСЬ ПОЛИНОМА";
	}
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	std::string left = msclr::interop::marshal_as< std::string >(textBox2->Text);
	std::string op = msclr::interop::marshal_as< std::string >(textBox3->Text);
	std::string right = msclr::interop::marshal_as< std::string >(textBox4->Text);

	int l, r;
	int ind;
	String^ s;
	try {
		size_t len;
		l = std::stoi(left, &len);

		if (len != left.length()) throw "";
		if (l < 1 || l > vec.size()) throw "";
		--l;
	}
	catch (...) { textBox2->Text = "НЕПРАВИЛЬНОЕ ЗНАЧЕНИЕ"; }

	if (op == "DEL") {
		for (int i = l + 1; i < vec.size(); ++i) vec[i - 1] = vec[i];
		vec.pop_back();

		dataGridView1->Rows->Clear();

		for (int i = 0; i < vec.size(); ++i) {
			dataGridView1->Rows->Add();
			dataGridView1->Rows[i]->Cells[0]->Value = i + 1;
			String^ s = gcnew String(vec[i].ToString().c_str());
			dataGridView1->Rows[i]->Cells[1]->Value = s;
		}
	}
	else if (op.length() == 1) {
		char c = op[0];

		try {
			size_t len;
			r = std::stoi(right, &len);

			if (len != right.length()) throw "";
			if (r < 1 || r > vec.size()) throw "";
			--l;
		}
		catch (...) { textBox2->Text = "НЕПРАВИЛЬНОЕ ЗНАЧЕНИЕ"; }
		try {
			switch (c) {
			case '+':
				vec.push_back(vec[l] + vec[r]);
				ind = dataGridView1->Rows->Add();
				dataGridView1->Rows[ind]->Cells[0]->Value = ind + 1;
				s = gcnew String(vec[ind].ToString().c_str());
				dataGridView1->Rows[ind]->Cells[1]->Value = s;
				break;
			case '-':
				vec.push_back(vec[l] + vec[r]);
				ind = dataGridView1->Rows->Add();
				dataGridView1->Rows[ind]->Cells[0]->Value = ind + 1;
				s = gcnew String(vec[ind].ToString().c_str());
				dataGridView1->Rows[ind]->Cells[1]->Value = s;
				break;
			case '*':
				vec.push_back(vec[l] * vec[r]);
				ind = dataGridView1->Rows->Add();
				dataGridView1->Rows[ind]->Cells[0]->Value = ind + 1;
				s = gcnew String(vec[ind].ToString().c_str());
				dataGridView1->Rows[ind]->Cells[1]->Value = s;
				break;
			case '/':
				if (vec[r].GetLength() != 1) throw "";
				vec[r].Reset();
				vec.push_back(vec[l] / vec[r].GetCurr()->value);
				ind = dataGridView1->Rows->Add();
				dataGridView1->Rows[ind]->Cells[0]->Value = ind + 1;
				s = gcnew String(vec[ind].ToString().c_str());
				dataGridView1->Rows[ind]->Cells[1]->Value = s;
				break;
			case '=': 
				vec[l] = vec[r];
				dataGridView1->Rows[l]->Cells[0]->Value = l+1;
				s = gcnew String(vec[l].ToString().c_str());
				dataGridView1->Rows[l]->Cells[1]->Value = s;
				break;
			}
		}
		catch (...) {
			textBox1->Text = "НЕ";
			textBox2->Text = "УДАЛОСЬ";
			textBox3->Text = "ВЫПОЛНИТЬ";
		}
	}
	else textBox3->Text = "НЕПРАВИЛЬНАЯ ОПЕРАЦИЯ";
}
};
}
