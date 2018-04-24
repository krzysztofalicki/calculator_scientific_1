#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <math.h>
using namespace std;



typedef struct node Node;

struct node {
	char znak;
	double liczba;
	int prior;
	Node *next;
	Node *prev;
};



Node *createzero (){
	
	Node *nev;
	nev = new (Node);
	nev->znak = '0';
	nev->liczba = 0;
	nev->prior = 0;
	nev->next = NULL;
	nev->prev = NULL;
	
	return nev;
}



Node *addlastzero (Node **head, Node **tail){
	
	Node *tmp = createzero();
	
	if (*head == NULL)
		*head = tmp;
	else{
		Node *pom = *head;
		while (pom->next != NULL)
			pom = pom->next;
		pom->next = tmp;
		tmp->prev = pom;
	}
	
	*tail = tmp;
	
	return *tail;
}



void deletecurrent (Node **current, Node **head){
	
	if ((*current) == (*head)){
		(*head) = ((*current)->next);
		((*current)->next)->prev = NULL;
	}
	
	else {
		((*current)->next)->prev = ((*current)->prev);
		((*current)->prev)->next = ((*current)->next);
	}
	
	delete (*current);
	
}



Node *moveleft (Node **current){
	
	*current = (*current)->prev;
	
	return *current;
}



Node *moveright (Node **current){
	
	*current = (*current)->next;
	
	return *current;
}



void showall (Node *head){
	
	if (head == NULL)
	cout << "empty!";
	
	else{
		Node *pom = head;
		while (pom->next != NULL){
			cout << pom->liczba;
			cout << pom->znak;
			cout << pom->prior;
			pom = pom->next;
		}
		cout << pom->liczba;
	}
}




int countall (Node *head){
	
	int i;
	
	if (head == NULL)
	i = 0;
	
	else{
		Node *pom = head;
		i = 1;
		while (pom->next != NULL){
			i++;
			pom = pom->next;
		}
	}
	
	return i;
}











int main (void){
	
	Node *head = NULL, *tail = NULL;
	Node *current = NULL;
	Node *temp = NULL;
	
	string wyraz;
	wyraz.c_str();
	
	cout << "Jestem kalkulatorem!!! Co chcesz obliczyc???" << endl;
	
	cin >> wyraz;
	
	int dlugosc = 0;
	dlugosc = wyraz.length();
	
	int n = 0;
	
	while (n < dlugosc){
		
		int odkad = n;
		string pom;
	
		while ((wyraz[n] >= '0' && wyraz[n] <= '9') || wyraz[n] == '.'){
			n++;
		}
		
		addlastzero(&head, &tail);
		pom = wyraz.substr(odkad,n);
		(tail->liczba) = atof(pom.c_str());
		
		if (n < dlugosc){
			
			(tail->znak) = wyraz[n];
			
			if (wyraz[n] == '+' || wyraz[n] == '-'){
				(tail->prior) = 1;
			}
			else if (wyraz[n] == '*' || wyraz[n] == ':'){
				(tail->prior) = 2;
			}
			else if (wyraz[n] == '^'){
				(tail->prior) = 3;
			}
			
			n++;
		}
	}
	
	int licznik = countall(head);
	licznik--;
	
	double wynik;
	
	while (licznik > 0){
		
		current = tail;
		
		while (current != head && (current->prev)->prior >= current->prior && current->znak != '^'){
			moveleft(&current);
		}
		
		if (current->znak == '+')
			wynik = current->liczba + (current->next)->liczba;
		else if (current->znak == '-')
			wynik = current->liczba - (current->next)->liczba;
		else if (current->znak == '*')
			wynik = current->liczba * (current->next)->liczba;
		else if (current->znak == ':')
			wynik = current->liczba / (current->next)->liczba;
		else if (current->znak == '^')
			wynik = pow(current->liczba, (current->next)->liczba);
		
		licznik--;
		
		(current->next)->liczba = wynik;
		
		deletecurrent (&current, &head);
	}
	
	cout << "= " << wynik << endl;
	
	
	

	
		
	system ("pause");
	return 0;
}

