#ifndef SESSION_H
#define SESSION_H

#include <QJsonObject>
#include <QString>




class Session
{
public:
    Session(){}
    Session(QString id, QString owner, int nop) : _id(id) , _owner(owner), _numOfPlayers(nop) {}
    ~Session(){}
    QString getId(){return _id;}
    QString getOwner(){return _owner;}
    int getNumOfPlayers(){return _numOfPlayers;}

    void readValuesFromJSON(QJsonObject &json){
        _id = json["id"].toString();
        _owner = json["owner"].toString();
        _numOfPlayers = json["numOfPlayers"].toInt();
    }

private:
    QString _id;
    QString _owner;
    int _numOfPlayers;

};

#endif // SESSION_H