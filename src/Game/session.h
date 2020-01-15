#ifndef SESSION_H
#define SESSION_H

#include <QJsonObject>
#include <QString>



/*!
 * \brief The Session class is used to parse and store session data recived from server
 */
class Session
{
public:
    /*!
     * \brief Session constructor
     */
    Session(){}
    /*!
     * \brief Session constructor
     * \param id ID of the session
     * \param owner of session
     * \param nop number of players
     */
    Session(QString id, QString owner, int nop) : _id(id) , _owner(owner), _numOfPlayers(nop) {}
    ~Session(){}
    /*!
     * \brief getId return ID of session
     * \return ID of session
     */
    QString getId(){return _id;}
    /*!
     * \brief getOwner returns owner of session
     * \return nickname of owner
     */
    QString getOwner(){return _owner;}
    /*!
     * \brief getNumOfPlayers returns number of players
     * \return number of players
     */
    int getNumOfPlayers(){return _numOfPlayers;}
    /*!
     * \brief getPlayersLimit reyurn player's limit
     * \return player's limit
     */
    int getPlayersLimit(){return _playersLimit;}
    /*!
     * \brief readValuesFromJSON parse info about session
     * \param json message from server about session
     */
    void readValuesFromJSON(QJsonObject &json)
    {
        _id = json["id"].toString();
        _owner = json["owner"].toString();
        _numOfPlayers = json["numOfPlayers"].toInt();
        _playersLimit = json["playersLimit"].toInt();
    }

private:
    /*!
     * \brief _id ID of session
     */
    QString _id;
    /*!
     * \brief _owner owner of session
     */
    QString _owner;
    /*!
     * \brief _numOfPlayers number of players
     */
    int _numOfPlayers;
    /*!
     * \brief _playersLimit limit of players in session
     */
    int _playersLimit;

};

#endif // SESSION_H
