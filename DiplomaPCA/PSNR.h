#pragma once
#include"XImage.h"
#include"XPSNR.h"
#include "XiTree.h"

namespace DiplomaPCA {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для PSNR
	/// </summary>
	public ref class PSNR : public System::Windows::Forms::Form
	{
	public:
		PSNR(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		XImage * img1;
		XImage * img2;
		XiBinTree* tree;

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~PSNR()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:

	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Left;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(240, 398);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &PSNR::pictureBox1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Dock = System::Windows::Forms::DockStyle::Right;
			this->pictureBox2->Location = System::Drawing::Point(241, 0);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(240, 398);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &PSNR::pictureBox2_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// treeView1
			// 
			this->treeView1->Dock = System::Windows::Forms::DockStyle::Right;
			this->treeView1->Location = System::Drawing::Point(481, 0);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(327, 428);
			this->treeView1->TabIndex = 1;
			this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &PSNR::treeView1_AfterSelect);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->pictureBox2);
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(481, 398);
			this->panel1->TabIndex = 3;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->richTextBox1->Location = System::Drawing::Point(0, 398);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(481, 30);
			this->richTextBox1->TabIndex = 2;
			this->richTextBox1->Text = L"";
			// 
			// PSNR
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(808, 428);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->treeView1);
			this->Name = L"PSNR";
			this->Text = L"Порівняння за PSNR";
			this->Load += gcnew System::EventHandler(this, &PSNR::PSNR_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

		void calcPsnr()
		{
			img1->init();
			img2->init();

			if ((img1->Width / (img1->Height + 0.0)) == (img2->Width / (img2->Height + 0.0)))
			{
				img1->PCA(3);
				img2->PCA(3);
				double temp = XPSNR::CalcPSNR(img1, img2);
				if (Double::IsInfinity(temp))
				{
					richTextBox1->Text = "Зображення ідентичні";
				}
				else
				{
					richTextBox1->Text = "PSNR= " + temp;
				}

			}
			else
			{
				richTextBox1->Text = "Розмір зображеннь не співпадає";
			}
			delete(img2);
		}

	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			img1 = new XImage(openFileDialog1->FileName);
		}

	}

	private: System::Void pictureBox2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			img2 = new XImage(openFileDialog1->FileName);
		}
	}
	private: System::Void PSNR_Load(System::Object^  sender, System::EventArgs^  e)
	{
		list<XiNode*> * nodes = tree->getAllNodes();
		for (std::list<XiNode*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
		{
			if ((*it)->content.size() > 1)
			{
				TreeNode^ tn = treeView1->Nodes->Add((*it)->value.ToString());
				for each (XImage* img  in (*it)->content)
				{
					TreeNode^ el = tn->Nodes->Add(Xhelper::stdStrToSysStr(img->Path));
					el->Tag = "element";
				}
			}
		}
	}

	private: System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
	{
		if (treeView1->SelectedNode->Tag == "element")
		{
			pictureBox2->ImageLocation = treeView1->SelectedNode->Text;
			img2 = new XImage(treeView1->SelectedNode->Text);
		}
		else
		{
			pictureBox2->ImageLocation = treeView1->SelectedNode->Nodes[0]->Text;
			img2 = new XImage(treeView1->SelectedNode->Nodes[0]->Text);
		}
		calcPsnr();
	}
	};
}
