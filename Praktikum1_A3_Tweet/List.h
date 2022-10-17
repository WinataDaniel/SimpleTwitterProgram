#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
//#include "catch.hpp"
#include <iostream>
#include <string>

template <typename T>
class List
{
    /*
    Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse
    List kann ein Stapel oder Warteschlange realisiert werden.
    */
private:
    struct form
    {
        std::string start = "<< ";
        std::string zwischen = ", ";
        std::string ende = " >>\n";
    } list_form;
    Node<T>* head_tail; // Zeiger auf Kopf- und End-Element -> next der 1. Knoten;
                     // -> prev der letzte Knoten
    int  list_size;  // Länge der Kette
    bool temp; // normalerweise false; ist true, wenn es sich um eine temor�re
               // Liste handelt die innerhalb der überladenen Operatoren
               // angelegt wird
public:
    List();
    List(const List<T>& _List); // Kopie Konstruktor
    ~List();
    void insertFront(T value);     // Einfügen eines Knotens am Anfang
    void insertFront(List<T>& _List); // Einfügen einer vorhandenen Liste am Anfang
    void insertBack(T value);      // Einfügen eines Knotesn am Ende
    void insertBack(List<T>& _List);  // Einfügen einer vorhandenen Liste am Ende
    bool getFront(T& value);       // Entnehmen eines Knoten am Anfang
    bool getBack(T& value);        // Entnehmen eines Knoten am Ende
    bool del(T value);             // löschen eines Knotens [key]
    bool search(T value);          // Suchen eines Knoten
    bool swap(T value1, T value2); // Knoten in der Liste vertauschen
    int  size(void);               // Größe der Lise (Anzahl der Knoten)
    bool test(void);               // Überprüfen der Zeigerstruktur der Liste
    void format(const std::string& start,
        const std::string& zwischen,
        const std::string& ende);
    // Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
    // start: stirng vor der Ausgabe der Liste
    // zwischen: string zwischen Listenknoten
    // ende: string am Ende der Liste
    List<T>& operator=(const List<T>& _List); // Zuweisungsoperator definieren
    List<T>&
        operator+(const List<T>& List_Append); // Listen zusammenführen zu einer Liste
    friend Node<T>* get_anker(List<T>& l);
    friend int   get_AnzahlNodes(List<T>& l);

    // Ausgabeoperator überladen
    template <typename T>
    friend std::ostream& operator << (std::ostream& stream, const List<T>& Liste);
};

template <typename T>
List<T>::List()
{
    /*
        Konstruktor für eine leere Liste
    */
    head_tail = new Node<T>;
    list_size = 0;
    temp = false;
    head_tail->next = head_tail;
    head_tail->prev = head_tail;
}

template <typename T>
List<T>::List(const List<T>& _List)
{
    /*
        Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
        in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
        sollen.
    */
    list_form = _List.list_form;
    head_tail = new Node<T>;
    list_size = 0;
    temp = _List.temp;
    head_tail->next = head_tail;
    head_tail->prev = head_tail;
    Node<T>* tmp_node;
    tmp_node = _List.head_tail->next;
    while (tmp_node != _List.head_tail)
    {
        head_tail->prev =
            new Node<T>(tmp_node->value, head_tail->prev->next, head_tail->prev);
        head_tail->prev->prev->next = head_tail->prev;
        list_size++;
        tmp_node = tmp_node->next;
    }
    /*
        Ist die übergebene Liste eine temporäre Liste? -> aus Operator +
    */
    if (_List.temp)
        delete& _List;
}

template <typename T>
List<T>::~List()
{
    //ToDo
/*
    Dekonstruktor
    Alle Knoten der Liste müssen gelöscht werden, wenn die Liste gelöscht wird.
*/
/*
if (list_size == 0) {
    delete head_tail;
    return;
}
*/

//  if (head_tail == nullptr) {
     // return;
  //}

    Node<T>* currentNode = head_tail->next;
    Node<T>* nextNode = currentNode->next;

    // Lösche alle Knoten und am Ende head_tail löschen.
    while (currentNode != head_tail) {
        head_tail->next = nextNode;
        nextNode->prev = head_tail;

        delete currentNode;
        currentNode = nextNode;
        nextNode = nextNode->next;
        list_size--;
    }
    delete head_tail;
}

template <typename T>
void List<T>::insertFront(T value)
{
    //ToDo
/*
    Einfuegen eines neuen Knotens am Anfang der Liste
    Einen neuen Knoten mit dem Wert value wird am Anfang der Liste einfügen
*/
// Erstelle einen neuen Knoten
    Node<T>* newNode = new Node<T>(value);
    newNode->prev = head_tail;
    newNode->next = head_tail->next;

    if (list_size == 0) {
        head_tail->next = newNode;
        head_tail->prev = newNode;
    }
    else {
        head_tail->next->prev = newNode;
        head_tail->next = newNode;
    }
    list_size++;
}

template <typename T>
void List<T>::insertFront(List<T>& _List)
{
    //ToDo
/*
    Einfuegen der Liste _List am Anfang an einer vorhandenen Liste
    Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
    Die einzufuegende Liste _List ist anschließend leer.
    Es darf keine Schleife und kein new benutzt werden.
*/

/*
    gleiches Objekt -> keine Aktion
*/
    if (head_tail == _List.head_tail) return;

    /*
        Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
        Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
        Die Liste _List ist danach leer, aber vorhanden.
    */

    // Erstellen von Hilfspointern
    Node* nextNodeList = head_tail->next;
    Node* nextNode_List = _List.head_tail->next;
    Node* lastNode_List = _List.head_tail->prev;

    // Verbinden head_tail Node mit dem ersten Node der _Liste
    nextNode_List->prev = head_tail;
    head_tail->next = nextNode_List;

    // Verbinden der letzte Node von der _Liste mit dem ersten Node von List
    lastNode_List->next = nextNodeList;
    nextNodeList->prev = lastNode_List;

    // umsetzen der next und prev Zeiger von _List
    _List.head_tail->next = _List.head_tail;
    _List.head_tail->prev = _List.head_tail;

    list_size = list_size + _List.list_size;
    _List.list_size = 0;
}

template <typename T>
void List<T>::insertBack(T value)
{
    //ToDo
/*
    Einfuegen eines neuen Knotens am Ende der Liste
    Einen neuen Knoten mit dem Wert value wird am Ende der Liste einfügen
*/

// Erstelle einen neuen Knoten
    Node<T>* newNode = new Node<T>(value);
    newNode->next = head_tail;
    newNode->prev = head_tail->prev;

    if (list_size == 0) {
        head_tail->next = newNode;
        head_tail->prev = newNode;
    }
    else {
        head_tail->prev->next = newNode;
        head_tail->prev = newNode;
    }
    list_size++;
}

template <typename T>
void List<T>::insertBack(List<T>& _List)
{
    //ToDo
/*
    Einfuegen der Liste _List am Ende einer vorhandenen Liste
    Die einzufuegenden Knoten werden uebernommen (nicht kopiert)
    Die einzufuegende Liste _List ist anschließend leer.
    Es darf keine Schleife und kein new benutzt werden.
*/

/*
    gleiches Objekt -> keine Aktion
*/
    if (head_tail == _List.head_tail) return;

    /*
        Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
        Diese Knoten (koplette Kette) werden an den Ende der Liste (this) übertragen ohne sie zu kopieren!
        Die Liste _List ist danach leer, aber vorhanden.
    */

    // Erstellen von Hilfspointern
    Node* lastNodeList = head_tail->prev;
    Node* nextNode_List = _List.head_tail->next;
    Node* lastNode_List = _List.head_tail->prev;

    // Verbinden der letzte Knoten von List mit dem erstem Knoten von _List
    lastNodeList->next = nextNode_List;
    nextNode_List->prev = lastNodeList;

    // Verbinden der letzte Knoten von _List mit head_tail von List
    lastNode_List->next = head_tail;
    head_tail->prev = lastNode_List;

    // Umsetzen der next und prev Zeiger von _List
    _List.head_tail->next = _List.head_tail;
    _List.head_tail->prev = _List.head_tail;

    list_size = list_size + _List.list_size;
    _List.list_size = 0;
}

template <typename T>
bool List<T>::getFront(T& value)
{
    //ToDo
/*
    entnehmen des Knotens am Anfang der Liste
    der Wert wird als Parameter zurueckgegeben
    der Knoten wird entnommen
    im Fehlerfall wird false zurückgegeben
*/

/*
    gleiches Objekt -> keine Aktion
*/
    if (!list_size) return false;


    //if (list_size == 0) return false;
    /*
        Der Wert des vorderen Knotens wird rückgegeben und der Knoten gelöscht.
        Die Methode del(value) darf nicht zum löschen benutzt werden.
    */
    Node<T>* firstNode = head_tail->next;
    value = firstNode->value;

    // Verbinden head_tail mit dem 2.Knoten
    head_tail->next = firstNode->next;
    firstNode->next->prev = firstNode->prev;

    delete firstNode;
    list_size--;
    return true;
}

template <typename T>
bool List<T>::getBack(T& value)
{
    //ToDo
/*
    entnehmen des Knotens am Ende der Liste
    der Wert wird als Parameter zurueckgegeben
    der Knoten wird entnommen
    im Fehlerfall wird false zurückgegeben
*/

/*
    gleiches Objekt -> keine Aktion
*/
    if (!list_size) return false;

    //if (list_size == 0) return false;

    /*
        Der Wert des letzten Knotens wird rückgegeben und der Knoten gelöscht.
        Die Methode del(value) darf nicht zum löschen benutzt werden.
    */
    Node<T>* lastNode = head_tail->prev;
    value = lastNode->value;

    // Verbinden vorletzter Knoten mit head_tail
    lastNode->prev->next = lastNode->next;
    head_tail->prev = lastNode->prev;

    delete lastNode;
    list_size--;
    return true;
}

template <typename T>
bool List<T>::del(T value)
{
    //ToDo
/*
    Loeschen eines gegebenen Knotens
    im Fehlerfall wird false zurückgegeben
*/

/*
    gleiches Objekt -> keine Aktion
*/
    if (!list_size) return false;

    /*
        Löschen des Knotens mit dem Wert value
    */
    Node<T>* currentNode = head_tail->next;

    while (currentNode->value != value && currentNode->next != head_tail) {
        currentNode = currentNode->next;
    }

    if (currentNode->value == value) {
        Node<T>* prevNode = currentNode->prev;
        Node<T>* nextNode = currentNode->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete currentNode;
        list_size--;
        return true;
    }
    return false;
}

template <typename T>
bool List<T>::search(T value)
{
    //ToDo
/*
    suchen eines Knotens
    nicht gefunden -> Rueckgabe: false
*/

/*
    leere Liste -> keine Aktion
*/
    if (!list_size) return false;

    /*
        suchen ob ein Knoten mit dem Wert value existiert.
    */
    Node<T>* currentNode = head_tail->next;

    while (currentNode->value != value && currentNode->next != head_tail) {
        currentNode = currentNode->next;
    }

    if (currentNode->value == value) {
        return true;
    }
    return false;
}

template <typename T>
bool List<T>::swap(T value1, T value2)
{
    //ToDo
/*
    Vertauschen von zwei Knoten
    Dabei werden die Zeiger der Knoten und deren Nachbarn veraendert.
    im Fehlerfall wird false zurueckgegeben
*/

/*
    Wenn Liste Leer oder weniger als 2 Knoten besitzt -> Keine Aktion
*/
    if (list_size < 2) return false;

    /*
        Vertauschen von zwei Knoten mit dem Wert value1 und dem Wert value2.
        Es duerfen nicht nur einfach die Werte in den Knoten getauscht werden!
        Die Knoten sind in der Kette umzuhaengen.
    */

    Node<T>* currentNode = head_tail->next;
    Node<T>* nodeV1 = nullptr;
    Node<T>* nodeV2 = nullptr;

    // Iterieren der Liste um value1 Node und value2 Node zu finden.
    while (currentNode != head_tail) {
        if (currentNode->value == value1 && nodeV1 == nullptr) nodeV1 = currentNode;
        if (currentNode->value == value2 && nodeV2 == nullptr) nodeV2 = currentNode;
        currentNode = currentNode->next;
    }

    if (nodeV1 == nullptr || nodeV2 == nullptr) return false;

    Node<T>* prevNodeV1 = nodeV1->prev;
    Node<T>* nextNodeV1 = nodeV1->next;
    Node<T>* prevNodeV2 = nodeV2->prev;
    Node<T>* nextNodeV2 = nodeV2->next;

    // Wenn V2 rechts von V1 steht.
    if (nextNodeV1 == nodeV2 && prevNodeV2 == nodeV1) {
        nodeV2->next = nodeV1;
        nodeV1->prev = nodeV2;

        prevNodeV1->next = nodeV2;
        nodeV2->prev = prevNodeV1;

        nodeV1->next = nextNodeV2;
        nextNodeV2->prev = nodeV1;
    }
    else if (nextNodeV2 == nodeV1 && prevNodeV1 == nodeV2) {
        nodeV1->next = nodeV2;
        nodeV2->prev = nodeV1;

        prevNodeV2->next = nodeV1;
        nodeV1->prev = prevNodeV2;

        nodeV2->next = nextNodeV1;
        nextNodeV1->prev = nodeV2;
    }
    else {

        prevNodeV1->next = nodeV2;
        nodeV2->prev = prevNodeV1;

        nodeV2->next = nextNodeV1;
        nextNodeV1->prev = nodeV2;

        prevNodeV2->next = nodeV1;
        nodeV1->prev = prevNodeV2;

        nodeV1->next = nextNodeV2;
        nextNodeV2->prev = nodeV1;
    }

    return true;
}

template <typename T>
int List<T>::size(void)
{
    //ToDo
/*
    Rueckgabe der Anzahl der Knoten in der Liste mit O(1)
    d.h. die Liste darf NICHT traversiert werden um die Größe zu bestimmen.

    Anzahl der Knoten in der Liste zurückgeben.
    Hier richtiges Ergebnis zurückgeben
*/
    return list_size;
}

template <typename T>
bool List<T>::test(void)
{
    // Testmethode: die Methode durchläuft die Liste vom Anfang bis zum Ende und
    // zurück Es werden dabei die Anzahl der Knoten gezahlt. Stimmt die Anzahl
    // der Knoten überein liefert die Methode true
    Node<T>* tmp = head_tail->next;
    int   i_next = 0, i_prev = 0;
    while (tmp != head_tail)
    {
        tmp = tmp->next;
        if (i_next > list_size)
            return false;
        i_next++;
    }
    if (i_next != list_size)
        return false;
    tmp = head_tail->prev;
    while (tmp != head_tail)
    {
        tmp = tmp->prev;
        if (i_prev > list_size)
            return false;
        i_prev++;
    }
    return i_prev == i_next;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& _List)
{
    // in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden
    // sollen. Kopiert wird in das Objekt "this"
    if (this == &_List)
        return *this; //  !! keine Aktion notwendig
    list_form = _List.list_form;
    Node<T>* tmp_node;
    if (list_size)
    {
        Node<T>* tmp_del;
        tmp_node = head_tail->next;
        while (tmp_node !=
            head_tail) // Alle eventuell vorhandenen Knoten in this löschen
        {
            tmp_del = tmp_node;
            tmp_node = tmp_node->next;
            delete tmp_del;
        }
        list_size = 0;
        head_tail->next = head_tail;
        head_tail->prev = head_tail;
    }
    tmp_node = _List.head_tail->next; // Die Listen-Knotenwerte werden kopiert
    while (tmp_node != _List.head_tail)
    {
        insertBack(tmp_node->value);
        tmp_node = tmp_node->next;
    }
    if (_List.temp)
        delete& _List; // ist die übergebene Liste eine temporäre Liste? -> aus
                       // Operator +
    return *this;
}

template <typename T>
List<T>& List<T>::operator+(const List<T>& List_Append)
{
    // Die Methode +
    // Es werden zwei Listen aneinander gehangen.
    // Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue
    // Ergebnisliste.
    Node<T>* tmp_node;
    List<T>* tmp;
    if (temp)
    { // this ist eine temporäre Liste und kann verändert werden
        tmp = this;
    }
    else
    {
        tmp =
            new List<T>(*this); // this ist keine temporäre Liste -> Kopie erzeugen
        tmp->temp = true;    // Merker setzten, dass es sich um eine temporäre
                             // Liste handelt
    }
    if (List_Append.list_size)
    { // anhängen der übergebenen Liste an tmp
        tmp_node = List_Append.head_tail->next;
        while (tmp_node != List_Append.head_tail)
        {
            tmp->insertBack(tmp_node->value);
            tmp_node = tmp_node->next;
        }
    }
    if (List_Append.temp)
        delete& List_Append; // wurde eine temporäre Liste übergeben, dann wird
                             // diese gelöscht
    return *tmp;
}

template <typename T>
void List<T>::format(const std::string& start,
    const std::string& zwischen,
    const std::string& ende)
{
    // Setzen des Formates für die Ausgabesteuerung der Liste bei cout
    // das Format wird für den überladenen Operator << verwendet
    list_form.start = start;
    list_form.zwischen = zwischen;
    list_form.ende = ende;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, List<T> const& Liste)
{
    // Ausgabe der Liste mit cout
    stream << Liste.list_form.start;
    for (Node<T>* tmp = Liste.head_tail->next; tmp != Liste.head_tail;
        tmp = tmp->next)
        stream << tmp->value
        << (tmp->next == Liste.head_tail ? Liste.list_form.ende :
            Liste.list_form.zwischen);
    if (Liste.temp)
        delete& Liste; // wurde eine temporäre Liste übergeben, dann wird diese
                       // gelöscht
    return stream;
}

#endif
