#pragma once

#include"XiTree.h"
#include "XHelper.h"
#include <ctime>
#include <queue>
#include "PSNR.h"


namespace DiplomaPCA
{

	using namespace std;
	using namespace System;
	using namespace System::IO;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::ComponentModel;
	using namespace System::Data;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
		SortedSet<String^>^ formats = gcnew SortedSet<String^>();
		XImage * img;
		int timeRun = 0;
		int progress = 0;
		bool run = 0;
		double accuracy = 0.2;
		List<String^>^ Files = gcnew List<String^>();
		XiBinTree * tree = new XiBinTree();
		DateTime Time;

	private: System::Windows::Forms::Button^  button1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel3;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel4;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
			 /*Start button*/
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  відкритиФайлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  видалитиФайлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  відкритиПапкуЗФайломToolStripMenuItem;

	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::ToolStripMenuItem^  pSNRToolStripMenuItem;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Panel^  panel3;

	private: System::Windows::Forms::Label^  label3;
	private: System::ComponentModel::IContainer^  components;
			 /// <summary>
			 /// Обязательная переменная конструктора.
			 /// </summary>


#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Требуемый метод для поддержки конструктора — не изменяйте 
			 /// содержимое этого метода с помощью редактора кода.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
				 this->button1 = (gcnew System::Windows::Forms::Button());
				 this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
				 this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
				 this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
				 this->toolStripStatusLabel3 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->toolStripStatusLabel4 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
				 this->listBox1 = (gcnew System::Windows::Forms::ListBox());
				 this->button2 = (gcnew System::Windows::Forms::Button());
				 this->button3 = (gcnew System::Windows::Forms::Button());
				 this->button4 = (gcnew System::Windows::Forms::Button());
				 this->treeView1 = (gcnew System::Windows::Forms::TreeView());
				 this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
				 this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
				 this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				 this->відкритиФайлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->видалитиФайлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->відкритиПапкуЗФайломToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->pSNRToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
				 this->panel1 = (gcnew System::Windows::Forms::Panel());
				 this->panel2 = (gcnew System::Windows::Forms::Panel());
				 this->panel4 = (gcnew System::Windows::Forms::Panel());
				 this->panel3 = (gcnew System::Windows::Forms::Panel());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->statusStrip1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
				 this->contextMenuStrip1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
				 this->panel1->SuspendLayout();
				 this->panel2->SuspendLayout();
				 this->panel4->SuspendLayout();
				 this->panel3->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // button1
				 // 
				 this->button1->BackColor = System::Drawing::Color::Moccasin;
				 this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
				 this->button1->Font = (gcnew System::Drawing::Font(L"Arial Black", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(204)));
				 this->button1->Location = System::Drawing::Point(12, 9);
				 this->button1->Name = L"button1";
				 this->button1->Size = System::Drawing::Size(35, 35);
				 this->button1->TabIndex = 0;
				 this->button1->Text = L"+";
				 this->button1->UseVisualStyleBackColor = false;
				 this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
				 // 
				 // backgroundWorker1
				 // 
				 this->backgroundWorker1->WorkerSupportsCancellation = true;
				 this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::backgroundWorker1_DoWork);
				 this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::backgroundWorker1_RunWorkerCompleted);
				 // 
				 // statusStrip1
				 // 
				 this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
					 this->toolStripStatusLabel1,
						 this->toolStripStatusLabel2, this->toolStripProgressBar1, this->toolStripStatusLabel3, this->toolStripStatusLabel4
				 });
				 this->statusStrip1->Location = System::Drawing::Point(0, 398);
				 this->statusStrip1->Name = L"statusStrip1";
				 this->statusStrip1->Size = System::Drawing::Size(939, 22);
				 this->statusStrip1->TabIndex = 2;
				 this->statusStrip1->Text = L"statusStrip1";
				 // 
				 // toolStripStatusLabel1
				 // 
				 this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
				 this->toolStripStatusLabel1->Size = System::Drawing::Size(59, 17);
				 this->toolStripStatusLabel1->Text = L"Обробка ";
				 // 
				 // toolStripStatusLabel2
				 // 
				 this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
				 this->toolStripStatusLabel2->Size = System::Drawing::Size(118, 17);
				 this->toolStripStatusLabel2->Text = L"toolStripStatusLabel2";
				 // 
				 // toolStripProgressBar1
				 // 
				 this->toolStripProgressBar1->Margin = System::Windows::Forms::Padding(3, 3, 1, 3);
				 this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
				 this->toolStripProgressBar1->Size = System::Drawing::Size(300, 16);
				 // 
				 // toolStripStatusLabel3
				 // 
				 this->toolStripStatusLabel3->Name = L"toolStripStatusLabel3";
				 this->toolStripStatusLabel3->Size = System::Drawing::Size(0, 17);
				 // 
				 // toolStripStatusLabel4
				 // 
				 this->toolStripStatusLabel4->Name = L"toolStripStatusLabel4";
				 this->toolStripStatusLabel4->Size = System::Drawing::Size(0, 17);
				 // 
				 // timer2
				 // 
				 this->timer2->Enabled = true;
				 this->timer2->Interval = 1000;
				 this->timer2->Tick += gcnew System::EventHandler(this, &MainForm::timer2_Tick);
				 // 
				 // listBox1
				 // 
				 this->listBox1->FormattingEnabled = true;
				 this->listBox1->Location = System::Drawing::Point(12, 50);
				 this->listBox1->Name = L"listBox1";
				 this->listBox1->Size = System::Drawing::Size(117, 95);
				 this->listBox1->TabIndex = 3;
				 // 
				 // button2
				 // 
				 this->button2->BackColor = System::Drawing::Color::LightSkyBlue;
				 this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
				 this->button2->Font = (gcnew System::Drawing::Font(L"Arial Black", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(204)));
				 this->button2->Location = System::Drawing::Point(53, 9);
				 this->button2->Name = L"button2";
				 this->button2->Size = System::Drawing::Size(35, 35);
				 this->button2->TabIndex = 4;
				 this->button2->Text = L"-";
				 this->button2->UseVisualStyleBackColor = false;
				 this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
				 // 
				 // button3
				 // 
				 this->button3->BackColor = System::Drawing::Color::Firebrick;
				 this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
				 this->button3->Font = (gcnew System::Drawing::Font(L"Arial Black", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(204)));
				 this->button3->ForeColor = System::Drawing::Color::White;
				 this->button3->Location = System::Drawing::Point(94, 9);
				 this->button3->Name = L"button3";
				 this->button3->Size = System::Drawing::Size(35, 35);
				 this->button3->TabIndex = 5;
				 this->button3->Text = L"X";
				 this->button3->UseVisualStyleBackColor = false;
				 this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
				 // 
				 // button4
				 // 
				 this->button4->BackColor = System::Drawing::Color::Aquamarine;
				 this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
				 this->button4->Location = System::Drawing::Point(12, 151);
				 this->button4->Name = L"button4";
				 this->button4->Size = System::Drawing::Size(117, 23);
				 this->button4->TabIndex = 6;
				 this->button4->Text = L"Start";
				 this->button4->UseVisualStyleBackColor = false;
				 this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click);
				 // 
				 // treeView1
				 // 
				 this->treeView1->Dock = System::Windows::Forms::DockStyle::Right;
				 this->treeView1->Location = System::Drawing::Point(565, 0);
				 this->treeView1->Name = L"treeView1";
				 this->treeView1->Size = System::Drawing::Size(374, 398);
				 this->treeView1->TabIndex = 7;
				 this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::treeView1_AfterSelect);
				 // 
				 // trackBar1
				 // 
				 this->trackBar1->Dock = System::Windows::Forms::DockStyle::Left;
				 this->trackBar1->LargeChange = 10000000;
				 this->trackBar1->Location = System::Drawing::Point(0, 36);
				 this->trackBar1->Maximum = 1400000000;
				 this->trackBar1->Name = L"trackBar1";
				 this->trackBar1->Orientation = System::Windows::Forms::Orientation::Vertical;
				 this->trackBar1->Size = System::Drawing::Size(45, 362);
				 this->trackBar1->SmallChange = 100;
				 this->trackBar1->TabIndex = 8;
				 this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::None;
				 this->trackBar1->Value = 1;
				 this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &MainForm::trackBar1_ValueChanged);
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(3, 20);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(35, 13);
				 this->label1->TabIndex = 9;
				 this->label1->Text = L"label1";
				 // 
				 // pictureBox1
				 // 
				 this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->pictureBox1->Location = System::Drawing::Point(0, 0);
				 this->pictureBox1->Name = L"pictureBox1";
				 this->pictureBox1->Size = System::Drawing::Size(323, 275);
				 this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
				 this->pictureBox1->TabIndex = 10;
				 this->pictureBox1->TabStop = false;
				 // 
				 // richTextBox1
				 // 
				 this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
				 this->richTextBox1->Location = System::Drawing::Point(0, 275);
				 this->richTextBox1->Name = L"richTextBox1";
				 this->richTextBox1->ReadOnly = true;
				 this->richTextBox1->Size = System::Drawing::Size(323, 123);
				 this->richTextBox1->TabIndex = 11;
				 this->richTextBox1->Text = L"";
				 // 
				 // contextMenuStrip1
				 // 
				 this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					 this->відкритиФайлToolStripMenuItem,
						 this->видалитиФайлToolStripMenuItem, this->відкритиПапкуЗФайломToolStripMenuItem, this->pSNRToolStripMenuItem
				 });
				 this->contextMenuStrip1->Name = L"contextMenuStrip1";
				 this->contextMenuStrip1->Size = System::Drawing::Size(205, 92);
				 // 
				 // відкритиФайлToolStripMenuItem
				 // 
				 this->відкритиФайлToolStripMenuItem->Name = L"відкритиФайлToolStripMenuItem";
				 this->відкритиФайлToolStripMenuItem->Size = System::Drawing::Size(204, 22);
				 this->відкритиФайлToolStripMenuItem->Text = L"Відкрити файл";
				 this->відкритиФайлToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::відкритиФайлToolStripMenuItem_Click);
				 // 
				 // видалитиФайлToolStripMenuItem
				 // 
				 this->видалитиФайлToolStripMenuItem->Name = L"видалитиФайлToolStripMenuItem";
				 this->видалитиФайлToolStripMenuItem->Size = System::Drawing::Size(204, 22);
				 this->видалитиФайлToolStripMenuItem->Text = L"Видалити файл";
				 this->видалитиФайлToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::видалитиФайлToolStripMenuItem_Click);
				 // 
				 // відкритиПапкуЗФайломToolStripMenuItem
				 // 
				 this->відкритиПапкуЗФайломToolStripMenuItem->Name = L"відкритиПапкуЗФайломToolStripMenuItem";
				 this->відкритиПапкуЗФайломToolStripMenuItem->Size = System::Drawing::Size(204, 22);
				 this->відкритиПапкуЗФайломToolStripMenuItem->Text = L"Відкрити теку з файлом";
				 this->відкритиПапкуЗФайломToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::відкритиПапкуЗФайломToolStripMenuItem_Click);
				 // 
				 // pSNRToolStripMenuItem
				 // 
				 this->pSNRToolStripMenuItem->Name = L"pSNRToolStripMenuItem";
				 this->pSNRToolStripMenuItem->Size = System::Drawing::Size(204, 22);
				 this->pSNRToolStripMenuItem->Text = L"PSNR";
				 this->pSNRToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::pSNRToolStripMenuItem_Click);
				 // 
				 // trackBar2
				 // 
				 this->trackBar2->Dock = System::Windows::Forms::DockStyle::Right;
				 this->trackBar2->Location = System::Drawing::Point(61, 36);
				 this->trackBar2->Maximum = 100000;
				 this->trackBar2->Minimum = 1;
				 this->trackBar2->Name = L"trackBar2";
				 this->trackBar2->Orientation = System::Windows::Forms::Orientation::Vertical;
				 this->trackBar2->Size = System::Drawing::Size(45, 362);
				 this->trackBar2->TabIndex = 13;
				 this->trackBar2->TickStyle = System::Windows::Forms::TickStyle::None;
				 this->trackBar2->Value = 23000;
				 this->trackBar2->ValueChanged += gcnew System::EventHandler(this, &MainForm::trackBar2_ValueChanged);
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(68, 20);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(35, 13);
				 this->label2->TabIndex = 14;
				 this->label2->Text = L"label2";
				 // 
				 // checkBox2
				 // 
				 this->checkBox2->AutoSize = true;
				 this->checkBox2->Checked = true;
				 this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->checkBox2->Location = System::Drawing::Point(50, 4);
				 this->checkBox2->Name = L"checkBox2";
				 this->checkBox2->Size = System::Drawing::Size(56, 17);
				 this->checkBox2->TabIndex = 15;
				 this->checkBox2->Text = L"PSNR";
				 this->checkBox2->UseVisualStyleBackColor = true;
				 this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox2_CheckedChanged);
				 // 
				 // panel1
				 // 
				 this->panel1->Controls->Add(this->pictureBox1);
				 this->panel1->Controls->Add(this->richTextBox1);
				 this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->panel1->Location = System::Drawing::Point(242, 0);
				 this->panel1->Name = L"panel1";
				 this->panel1->Size = System::Drawing::Size(323, 398);
				 this->panel1->TabIndex = 16;
				 // 
				 // panel2
				 // 
				 this->panel2->Controls->Add(this->panel4);
				 this->panel2->Controls->Add(this->button3);
				 this->panel2->Controls->Add(this->button1);
				 this->panel2->Controls->Add(this->listBox1);
				 this->panel2->Controls->Add(this->button2);
				 this->panel2->Controls->Add(this->button4);
				 this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
				 this->panel2->Location = System::Drawing::Point(0, 0);
				 this->panel2->Name = L"panel2";
				 this->panel2->Size = System::Drawing::Size(242, 398);
				 this->panel2->TabIndex = 17;
				 // 
				 // panel4
				 // 
				 this->panel4->Controls->Add(this->trackBar2);
				 this->panel4->Controls->Add(this->trackBar1);
				 this->panel4->Controls->Add(this->panel3);
				 this->panel4->Dock = System::Windows::Forms::DockStyle::Right;
				 this->panel4->Location = System::Drawing::Point(136, 0);
				 this->panel4->Name = L"panel4";
				 this->panel4->Size = System::Drawing::Size(106, 398);
				 this->panel4->TabIndex = 18;
				 // 
				 // panel3
				 // 
				 this->panel3->Controls->Add(this->label3);
				 this->panel3->Controls->Add(this->label1);
				 this->panel3->Controls->Add(this->label2);
				 this->panel3->Controls->Add(this->checkBox2);
				 this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
				 this->panel3->Location = System::Drawing::Point(0, 0);
				 this->panel3->Name = L"panel3";
				 this->panel3->Size = System::Drawing::Size(106, 36);
				 this->panel3->TabIndex = 18;
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(0, 4);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(41, 13);
				 this->label3->TabIndex = 15;
				 this->label3->Text = L"Норма";
				 // 
				 // MainForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(939, 420);
				 this->Controls->Add(this->panel1);
				 this->Controls->Add(this->panel2);
				 this->Controls->Add(this->treeView1);
				 this->Controls->Add(this->statusStrip1);
				 this->MinimumSize = System::Drawing::Size(771, 270);
				 this->Name = L"MainForm";
				 this->Text = L"Пошук подібних зображень";
				 this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
				 this->statusStrip1->ResumeLayout(false);
				 this->statusStrip1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
				 this->contextMenuStrip1->ResumeLayout(false);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
				 this->panel1->ResumeLayout(false);
				 this->panel2->ResumeLayout(false);
				 this->panel4->ResumeLayout(false);
				 this->panel4->PerformLayout();
				 this->panel3->ResumeLayout(false);
				 this->panel3->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

	private:
		/*>Парсер всех файлов из папки */
		inline	 SortedSet<String^>^ foundFiles(String^ dirPath)
		{
			SortedSet<String^>^ files = gcnew SortedSet<String^>();
			for each (String^ file  in Directory::EnumerateFiles(dirPath))
			{
				files->Add(file);
			}
			for each (String^ dir  in Directory::EnumerateDirectories(dirPath))
			{
				for each (String^ file  in foundFiles(dir))
				{
					files->Add(file);
				}
			}

			return files;
		}

		System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e)
		{
			formats->Add("bmp");
			formats->Add("jpg");
			formats->Add("jpeg");
			CONFIG::getInstance().pcaNorm = 1;

			trackBar1->Value = 120000000;
			trackBar2->Value = 24000;
		}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			listBox1->Items->Add(folderBrowserDialog1->SelectedPath);
			listItemsChange();
		}
	}

	private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		if (run)
		{
			
			TimeSpan ^ts = DateTime::Now - Time;
			float que = (float)(progress / (ts->TotalSeconds + 0.0));
			toolStripStatusLabel3->Text = que + " Зображень/с";
			toolStripStatusLabel4->Text = "Залишилось приблизно " + ((Files->Count - progress) / que) + " c";
		}
		else
		{
			toolStripStatusLabel3->Text = ""; toolStripStatusLabel4->Text = "";
		}
		toolStripProgressBar1->Value = progress;
		toolStripStatusLabel2->Text = progress + "/" + Files->Count;

	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (listBox1->Items->Count > 0)
		{
			listBox1->Items->Clear();
			listItemsChange();
		}
	}
	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
	{
		button4->Text = "Stop";
		Time = DateTime::Now;
		progress = 0;

		run = 1;
		tree->clean();

#pragma omp parallel for 
		for (int i = 0; i < Files->Count; i++)
		{
			if (!run)
			{
				break;
			}

			XImage * temp = new XImage(Files[i]);

			try
			{
				tree->insert(new XImage(Files[i]));
			}
			catch (const std::exception&) {}

			progress++;
		}

		if (run)
		{
			progress = Files->Count;
		}

		run = 0;
		button4->Text = "Start";
		button4->Enabled = 1; button1->Enabled = 1; button2->Enabled = 1;  button3->Enabled = 1;
		trackBar1->Enabled = 1; trackBar2->Enabled = 1; checkBox2->Enabled = 1;
	}

			 /*Start button*/
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!run)
		{
			button1->Enabled = 0; button2->Enabled = 0;  button3->Enabled = 0;
			trackBar1->Enabled = 0; trackBar2->Enabled = 0; checkBox2->Enabled = 0;

			backgroundWorker1->RunWorkerAsync();
		}
		else
		{
			((Button^)sender)->Enabled = 0;
			run = 0;
		}
	}

			 void listItemsChange()
			 {
				 progress = 0;
				 Files->Clear();
				 SortedSet<String^>^ temp = gcnew SortedSet<String^>();
				 for each (String^ folder in listBox1->Items)
				 {
					 SortedSet<String^>^ ifiles = foundFiles(folder);
					 for each (String^ file in ifiles)
					 {
						 for each (String^ format in formats)
						 {
							 if ((file->Substring(file->Length - 3)->ToLower() == format))
							 {
								 temp->Add(file);
							 }
						 }
					 }
				 }
				 for each (String^ f in temp)
				 {
					 Files->Add(f);
				 }
				 toolStripProgressBar1->Maximum = Files->Count;
			 }

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (CONFIG::getInstance().acceptDelete)
		{
			if (listBox1->Items->Count > 0)
			{
				if (MessageBox::Show("Пiдтвердiть видалення", "Ви дiйсно бажаєте видалити " + listBox1->SelectedItem + "?", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
				{
					listBox1->Items->RemoveAt(listBox1->SelectedIndex);
					listItemsChange();
				}
			}
		}
	}

	private: System::Void trackBar1_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		if (trackBar1->Value < 500000000)
		{
			CONFIG::getInstance().accuracy = +(trackBar1->Value) / 500000000.0;
		}
		else
		{
			CONFIG::getInstance().accuracy = 1.0 + (trackBar1->Value - 500000000) / 100000000.0;
		}

		label1->Text = (CONFIG::getInstance().accuracy) + "";
		label1->Text = label1->Text->Substring(0, label1->Text->Length > 7 ? 7 : label1->Text->Length);
	}

	private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
	{
		treeView1->Nodes->Clear();
		list<XiNode*> * nodes = tree->getAllNodes();
		for (std::list<XiNode*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
		{
			if ((*it)->content.size() > 1)
			{
				TreeNode^ tn = treeView1->Nodes->Add((*it)->value.ToString());
				tn->Tag = false;
				for each (XImage* img  in (*it)->content)
				{
					TreeNode^ el = tn->Nodes->Add(Xhelper::stdStrToSysStr(img->Path));
					el->Tag = "element";
					el->ContextMenuStrip = contextMenuStrip1;
				}
			}
		}
	}

	private: System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
	{
		if (treeView1->SelectedNode->Tag == "element")
		{
			FileInfo ^ fn = gcnew FileInfo(treeView1->SelectedNode->Text);
			pictureBox1->ImageLocation = treeView1->SelectedNode->Text;
			richTextBox1->Text = "";
			richTextBox1->Text += "Назва		" + fn->Name + "\n";
			richTextBox1->Text += "Тип		" + fn->Extension + "\n";
			richTextBox1->Text += "Створено	" + fn->CreationTime + "\n";
			richTextBox1->Text += "Останній доступ	" + fn->LastAccessTime + "\n";
			long long size = fn->Length;
			size >>= 10;
			richTextBox1->Text += "Розмір		" + size   +" кб\n";

		}
		else
		{
			pictureBox1->ImageLocation = treeView1->SelectedNode->Nodes[0]->Text;
		}

	}

	private: System::Void trackBar2_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		CONFIG::getInstance().accuracyPSNR = trackBar2->Value / 1000.0;
		label2->Text = CONFIG::getInstance().accuracyPSNR.ToString();
	}

	private: System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		CONFIG::getInstance().psnrON = checkBox2->Checked;
		trackBar2->Enabled = CONFIG::getInstance().psnrON;
	}

	private: System::Void pSNRToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		PSNR ^psnrForm = gcnew PSNR();
		if (treeView1->SelectedNode->Tag == "element")
		{
			psnrForm->img1 = new XImage(treeView1->SelectedNode->Text);
			psnrForm->pictureBox1->ImageLocation = treeView1->SelectedNode->Text;
		}
		else
		{
			psnrForm->img1 = new XImage(treeView1->SelectedNode->Nodes[0]->Text);
			psnrForm->pictureBox1->ImageLocation = treeView1->SelectedNode->Nodes[0]->Text;
		}
		psnrForm->tree = tree;
		psnrForm->Show();
	}
	private: System::Void відкритиПапкуЗФайломToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		System::Diagnostics::Process::Start("explorer.exe", "\/select, " + treeView1->SelectedNode->Text);

	}
	private: System::Void відкритиФайлToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		System::Diagnostics::Process::Start("explorer.exe", treeView1->SelectedNode->Text);
	}
	private: System::Void видалитиФайлToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (MessageBox::Show("Підтвердіть видалення " +
			treeView1->SelectedNode->Text, "",
			MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
		{

			System::IO::File::Delete(treeView1->SelectedNode->Text);
			treeView1->Nodes->Remove(treeView1->SelectedNode);
		}
	}
	};
}
