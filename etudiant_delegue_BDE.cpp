#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class Etudiant {
    protected :
    string nom;
    string prenom;
    vector <string> matiere;
    vector <float> note;
    int abscence;
    public :
    Etudiant(string nom , string prenom)=delete;
    Etudiant(string nom, string prenom,string matiere, float note){
        this->nom=nom;
        this->prenom=prenom;
        this->abscence=0;
        this->matiere.push_back(matiere);
        this->note.push_back(note);
    }
    void setInfo(string nomMatiere , int note){
        auto posMatiere = find(matiere.begin(), matiere.end(),nomMatiere);
        if (posMatiere != matiere.end())
        {
            cout<<"la matiere existe deja"<<endl;
        } else {
            matiere.push_back(nomMatiere);
            this->note.push_back(note);
        }
    }
    
    void affichae(){
        cout<<"les informations de l'etudiant : "<<endl;
        cout<<"Nom : "<<nom<<endl;
        cout<<"prenom : "<<prenom<<endl;
        cout<<"matiere : "<<endl;
        for (auto i=0 ;i < matiere.size() ; i++){
            cout<<matiere[i]<<endl;
        }
        cout<<"note"<<endl;
        for (auto i=0 ;i<note.size();i++){
            cout<<note[i]<<endl;
        }
        cout<<"abscence : "<<abscence<<endl;
    }
    
    float moyenne(){
        float somme = 0;
        for (auto i=0;i< note.size() ; i++){
            somme +=note[i];
        }
        return somme/note.size();
    }
    
    void suppression(){
        for (auto i = 0; i < note.size(); ++i) {
            if (note[i] < 10.0) {
                note.erase(note.begin() + i);
                matiere.erase(matiere.begin() + i);
                --i;
            }
        }
    }

    void avertissement() {
        if (abscence > 15) {
            cout << "Attention! Vous avez dépassé 15 absences. Veuillez prendre des mesures." << endl;
        } else {
            cout << "Nombre d'absences dans les limites acceptables." << endl;
        }
    }

    void bonus() {
        bool allGradesAbove12 = all_of(note.begin(), note.end(), [](float n) { return n > 12.0; });
        if (allGradesAbove12 && abscence < 3) {
            cout << "Félicitations" << endl;
        } else {
            cout << "Pas de bonus cette fois-ci." << endl;
        }
    }
    friend void NoteMax(Etudiant etu);
    
};

void NoteMax(Etudiant etu ){
    float max=0;
    int indix;
    int i;
    for (i=0;i<etu.note.size();i++){
        if(etu.note[i]>max){
            max=etu.note[i];
            indix=i;
        }
    }
    cout <<etu.nom<<" la note : "<<max<<" matier : "<<etu.matiere[i]<<endl;
    
};

class Delegue : public Etudiant{
    protected :
    int Num_tele;
    vector <string> Enseignant;
    vector <int> Date_exam;
    public :
    Delegue (string nom,string prenom,string mat,float note ,int num) : Etudiant(nom,prenom,mat,note)  {
        this->Num_tele = num;
    };
    
    void modifier_date(int date) {
        auto posDate = find(Date_exam.begin(), Date_exam.end(),date);
        if (posDate != Date_exam.end())
        {
            cout<<"la date existe deja"<<endl;
        } else {
            Date_exam.push_back(date);
        }
    }
    
    void annuler_seance(string teacher) {
        auto posSub = find(Enseignant.begin(), Enseignant.end(),teacher);
        if (posDate != Enseignant.end())
        {
            note.erase(note.begin() + posDate);
            matiere.erase(matiere.begin() + posDate);
            cout<<"la seance est annuler"<<endl;
        } else {
            cout<<"teacher does not exist"<<endl;
        }
    }
};


class BDE : public Delegue{
    protected :
    int id;
    public :
    BDE (int id, string nom,string prenom,string mat,float note ,int num) : Delegue(nom,prenom,mat,note, num) {};
    
    void planifier_evenement(string event, int date) {
        auto posDate = find(Date_exam.begin(), Date_exam.end(),date);
        if (posDate != Date_exam.end())
        {
            cout<<"you cant plan it, it colides with an exam date"<<endl;
        } else {
            cout<<"event '" << event << "' is planned for " << date << "." <<endl;
        }
    };

};


class Group {
private:
    string name;
    string subject;
    vector<Etudiant> students;
public:
    Group(string name, string subject){
        this->name = name;
        this->subject = subject;
    }
    
    void add_student(Etudiant s){
        students.push_back(s);
    }
    
    void moyenne_groupe(){
        cout<<"name : "<<name<<endl;
        cout<<"subject : "<<subject<<endl;
        
        float sum = 0;
        for (auto i=0; i< students.size() ; i++){
            sum += students[i].moyenne();
        }
        
        cout<<"moyenne : "<<sum / students.size() <<endl;
    }

    friend Group operator/(const Group &group1, const Group &group2) {
        float avgGradeGroup1 = group1.calculateAverageGrade();
        float avgGradeGroup2 = group2.calculateAverageGrade();

        if (avgGradeGroup1 > avgGradeGroup2) {
            cout << "Group Name: " << group1.name << " has the maximum average grade" << endl;
            return group1;
        } else if (avgGradeGroup1 < avgGradeGroup2) {
            cout << "Group Name: " << group2.name << " has the maximum average grade" << endl;
            return group2;
        } else {
            cout << "Both groups have the same average grade" << endl;
            return group1;
        }
    }

    float calculateAverageGrade() const {
        if (students.empty()) {
            return 0;
        }

        float sum = 0;
        for (const auto &i : students) {
            sum += i.moyenne();
        }

        return sum / students.size();
    }
    
};

