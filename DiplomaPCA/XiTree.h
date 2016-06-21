#pragma once

#include "XImage.h"
#include "XPSNR.h"
#include <iostream>
#include <queue>
#include <list>
namespace DiplomaPCA
{
	using namespace std;

	/*нода бинарного древа*/
	struct XiNode
	{
		double value;
		list<XImage *> content;
		XiNode *left, *right;
	};

	/*Бинарное древо поиска
	>Внутри ноды есть список с повторяющимеся ключами
	>Ключ к нодам- норма изображения*/
	class XiBinTree
	{

		XiNode *_root = NULL;

	public:
		int copies = 0;
		/*пустой конструктор, ага!*/
		XiBinTree::XiBinTree() {	}

		/*деструктор, о да в нем чтото есть, АГА!*/
		XiBinTree::~XiBinTree()
		{
			del(_root);
		}


		list<XiNode*>* getAllNodes()
		{
			list<XiNode*> *lis = new list<XiNode*>();



			searchNodes(_root, lis);

			return lis;
		}

		inline void XiBinTree::searchNodes(XiNode *& Tree, list<XiNode*> *q)
		{
			if (Tree != NULL)
			{
				searchNodes(Tree->left, q);

				q->push_back(Tree);

				searchNodes(Tree->right, q);
			}
		}

		/*печать на екран(покашто) используя обходы внутри проги*/
		inline void XiBinTree::show()
		{
			cout << endl << endl;
			cout << "SORTED" << endl;
			showSorted(_root);
			cout << endl << endl;
			cout << "REV SORTED" << endl;
			showRevSorted(_root);
			cout << endl << endl;
			cout << "showTree" << endl;
			showTree(_root);
			cout << endl << endl;
			cout << "showLayer" << endl;
			showLayer(_root);
			cout << endl << endl;
			cout << endl << endl;
			cout << "Copies- " << copies << endl;
		}

		inline void getCopies() {
			_getCopies(_root);
		}

		inline void getSimilar(float range) {
			_getSimilar(_root, range);
		}

		inline void clean()
		{
			del(_root);
			copies = 0;
		}


		inline void XiBinTree::insert(XImage * value)
		{
			insert(value, _root);
		}
	private:

		inline void XiBinTree::insert(XImage * Value, XiNode *& cNode)
		{
			if (NULL == cNode)
			{
				//cout << "node " << Value->Norma << " " << Value->Path << endl;
				cNode = new XiNode;
				cNode->value = Value->Norma;
				cNode->content.push_back(Value);
				cNode->left = cNode->right = NULL;

				return;
			}
			else
			{
				double accur = CONFIG::getInstance().accuracy;

				if (cNode->value - accur <= Value->Norma)
				{
					if (cNode->value + accur >= Value->Norma)
					{
						if (!CONFIG::getInstance().psnrON)
						{
							cNode->content.push_back(Value);
							copies++;
							return;
						}
						else
						{
							if (XPSNR::PSNR(cNode->content.front(), Value))
							{
								cNode->content.push_back(Value);
								copies++;
								return;
							}
							else
							{
								if (cNode->value < Value->Norma)
								{
									insert(Value, cNode->left);
									return;
								}

								else
								{
									insert(Value, cNode->right);
									return;
								}
							}
						}

					}
					else
					{
						insert(Value, cNode->right);
						return;
					}
				}
				else
				{
					insert(Value, cNode->left);
					return;
				}

			}
		}



		inline void XiBinTree::showSorted(XiNode *& Tree)
		{
			if (Tree != NULL)
			{
				showSorted(Tree->left);
				cout << "NODE " << Tree->value << endl;

				for each (XImage* var in Tree->content)
				{
					cout << "	element " << var->Path << endl;
				}

				showSorted(Tree->right);
			}
		}

		inline void XiBinTree::showLayer(XiNode *& Tree)
		{
			if (Tree == NULL)
			{
				cout << " empty " << endl;
				return;
			}

			queue<XiNode*> q;
			q.push(Tree);

			while (!q.empty())
			{
				XiNode* x = q.front();
				q.pop();
				cout << x->value << endl;

				if (NULL != x->left)
				{
					q.push(x->left);
				}

				if (NULL != x->right)
				{
					q.push(x->right);
				}
			}
		}
		inline void XiBinTree::showRevSorted(XiNode *& Tree)
		{
			if (Tree != NULL)
			{
				showRevSorted(Tree->right);
				cout << Tree->value << endl;
				showRevSorted(Tree->left);
			}
		}
		inline void XiBinTree::showTree(XiNode *& Tree)
		{
			if (Tree != NULL)
			{
				cout << Tree->value << endl;
				showTree(Tree->left);
				showTree(Tree->right);
			}
		}

		inline void _getCopies(XiNode *& Tree)
		{
			if (Tree != NULL)
			{
				_getCopies(Tree->left);

				if (Tree->content.size() > 1)
				{
					cout << "NODE " << Tree->value << endl;

					for each (XImage* var in Tree->content)
					{
						cout << "	element " << var->Path << endl;
					}
				}


				_getCopies(Tree->right);
			}
		}

		inline void	_getSimilar(XiNode *& Tree, float range) {
			if (Tree != NULL)
			{
				_getCopies(Tree->left);

				if (Tree->content.size() > 1)
				{
					cout << "NODE " << Tree->value << endl;

					for each (XImage* var in Tree->content)
					{
						cout << "	element " << var->Path << endl;
					}
				}


				_getCopies(Tree->right);
			}
		}


		inline void XiBinTree::del(XiNode *&cNode)
		{
			if (cNode != NULL) //Пока не встретится пустое звено
			{
				for each (XImage* image in cNode->content)
				{
					delete(image);
				}
				cNode->content.clear();
				del(cNode->left); //Рекурсивная функция прохода по левому поддереву
				del(cNode->right); //Рекурсивная функци для прохода по правому поддереву

				delete cNode; //Убиваем конечный элемент дерева
				cNode = NULL; //Может и не обязательно, но плохого не будет
			}
		}
	};


}