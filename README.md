﻿Проект создан под Windows x64, Qt 6.6.0.

При установке приложения в "C:\Program Files", если вы хотите чтобы открывалась база данных для записи сообщений, необходимо запускать приложение от имени администратора. Если у вас нет прав администратора, то устанавивайте приложение в "C:\Users\User\...".

### Перед запуском приложения проверьте наличие файла базы данных messages_db.accdb в папке с исполняемым файлом. Если файла базы данных там нет, скопируйте его туда из папки с проектом.
    
---
    
# ОПИСАНИЕ ГРАФИЧЕСКОГО ИНТЕРФЕЙСА И ВЗАИМОДЕЙСТВИЯ С НИМ      

В верхней части окна расположены элементы для запуска сервера:
- поле для ввода номера порта;
- кнопка для запуска сервера;
- индикатор статуса сервера;

В нижней части окна расположены элементы:
- для отображения принятых, отправленных и информативных сообщенияй;
- для отображения списка имен подключенных клиентов;
- для ввода и отправки сообщений клиентам.

Номер порта должен быть от 49152 до 65535. При выходе за пределы этих значений, вводимый текс станет красным, а кнопка "start" станет неактивна. После ввода номера порта нажмите кнопку "start" для запуска сервера. Если сервер был запущен, индикатор станет зеленым и надпись изменится на "connected", поле для ввода номера порта станет неактивным, выведутся сообщения с IP-адресом, номером порла и статусом подключения к БД. Также станет активно поле для ввода сообщения клиентам. Кнопка "send" станет активна как только будет введен хотя бы один символ в поле для ввода сообщений.

Если сервер не был запущен, то будет выведено сообшение об ошибке.

Для остановки сервера нажмите "stop". При необходимости измените значения номера порта и снова нажмите "start".

При подключении нового клиента к серверу, будет выведено сообщение о подключении нового клиента и он появится в списке. Если клиент с таким же именем уже был подключен, то новому клиенту будет присвоено новое имя (имя_клиента + '1') и отправлено соответствующее сообщение с новым именем. При отключении клиента также будет выведено сообщение.

---

# ОПИСАНИЕ БАЗЫ ДАННЫХ

База данных имеет формат MS Access и содержит одну таблицу со следующими столбцами:
- id_msg (bigint auto increment primary key) - ID сообшения;
- sender_name (nvarchar(255) not null) - имя отправителя;
- sender_address (nvarchar(255) not null) - IP-адрес отправителя;
- msg_text (nvarchar(max) not null) - текст сообшения;
- send_time (datetime not null) - дата и время отправки сообщения.

---

# ОПИСАНИЕ КЛАССОВ

---

## ServerModel

Класс, описывающий логические процессы серверного приложения.

### Атрибуты

##### private:

```MessagesDB *messages_db``` - объект класса, содержащего базу дынных.
```quint16 next_block_size``` -длина следующего полученного блока данных от клиента.
```quint16 port_num``` - номер порта для подключения клиентов.
```QTcpServer *server``` - объект сервера.
```bool stateServer``` - статус работы сервера.
```QMap <QTcpSocket*, QString> clients``` - словарь подключенных клиентов, где ключ - указатель на объект сокетв клиента, а значение - имя клиента.

### Конструкторы

##### public

```explicit ServerModel(QObject *parent = nullptr)``` - В него передается указатель на объект-предок для соблюдения принципов иерархического создания и удаления объектов. Здесь же инициализируется объект сервера и ```port_num```, ```messages_db```, ```next_block_size``` присваиваются нулевые значения.

### Методы

##### private:

```bool sendMsgToClient(const QString &message, QTcpSocket* client_socket)``` - в качестве параметров принимает строку с текстом сообщения и указатель на объект сокета клиента.Преобразует сообщение в поток данных и записывает их в сокет клиента и записывает сообщение в базу данных. Возвращает ```true``` при выполнении всего тела метода.

##### public:

```bool getStateServer() const``` - возвращает статус работы сервера.

```bool sendMsgToClient(const QString& client, const QString& message)``` - принисает в качестве параметров 2 строки - имя клиента и текст сообшения. Если имя клиента содержится в словаре, то возвращается результат выполнения метода ```sendMsgToClient(message, clients.key(client))```, а если нет - возвращается ```false```.

```bool startServer(const QString& s_port)``` - метод для запуска сервера. При успешном запуске возвращается значение ```true```. В метод передается строка, содержащая номер порта. В теле метода инициализируется объект сервера и объект адреса, которому присваивается IP-адрес, взятый из списка доступных адресов.
Следом идет попытка запуска сервера при помощи метода ```listen```. Если метод ```listen``` вернул значение ```false```, то издается сигнал с передачей в него сообшения с текстом ошибки и возвращается значение ```false```. Если сервер запустился, то отправлется сигнал для вывода сообщения на графический интерфейс с информацией о запущеном сервере. Далее соединяется сигнал ```newConnection``` со слотом ```slotNewConnection``` и ```acceptError``` с лямбдой, в которой испускаются сигнлы ```stateServerChanged``` и ```errorServer```. В конце метода инициализируется объект для работы с базой данных.
В зависимости от успеха открытия базы данных, на графический интерфейс отправляются
соответсвующие сообщения. Атрибуту ```stateServer``` присваивается состояние сервера
и он жн возвращается методом.

```bool stopServer()``` - возвращает ```true``` при успешной остановке сервера. Атрибуту ```stateServer``` присваивается значение ```false```, объект сервера вызывает метод ```close```. Далее в цикле происходит отключение всех клиентов от сервера и очищается словарь клиентов. Закрывается и удаляется объект базы данных. На графический интерфейс отправляется сообщение о закрытии сервера.

##### private slots:

 ```void slotClientDisconnected()``` - слот вызывается при отключении клиента от сервера. Отправляется соответствующий сигнал для удаления клиента из списка в графическом интерфейсе, после чего, удаляется из словаря клиентов.

```void slotNewConnection()``` - слот вызывается при наличии нового входящего подключения к серверу. В словарь  ключом записывается указатель на новый сокет с пустым значением. Соудиняются сигналы ```disconnected``` и ```readyRead``` со слотами ```slotClientDisconnected```, ```slotReadFromClient```.

```void slotReadFromClient()``` - слот вызывается при получении сервером входящего сообщения. Создается поток, при помощи которого происходит считывание сообшения в строку, и временный сокет, от которого и поступило сообщение. Далее проверяется наличие значения этого сокета в словаре клиентов. Если значение пустое - то в него записывается сообщение, являющееся именем клиента, которое клиент отправляет сразу же после подключения. Если такое значение уже есть, то записывается новое значение, состоящее из проверяемого значения и cчетчика количества таких же имен. Если и это имя занято, то операция добавления 1 продолжается. По итогу присваивания нового значения имени, этому клиенту отправляется соответсвующее сообшение с новым именем. В графический интерфейс передается имя клиента, для добавления его в список подключеннных клиентов. Если клиент уже был добавлен в словарь ранее, то производится отправка сигнала с текстом сообщения для вывода его в графический интерфейс и осуществляется запись сообщения в базу данны.

### Сигналы

```void clientName(QString)``` - сигнал, содержащий имя клиента.
```void errorServer(QString)``` - сигнал об ошибке с передачей строки с ее описанием.
```void sendMsgToGUI(QString)``` - сигнал, отправляющий текст сообщения на графический интерфейс
```void removeClientFromList(QString)``` - сигнал, отправляющий имя клиента в графический интерфейс для его последующего удления из списка.
```void stateServerChanged(bool)``` - сигнал с новым статусом работы сервера.

---

## ServerViewModel

Класс-прослойка между классом модели сервера и его представлением.

### Атрибуты

##### private:

```ServerModel* server_model``` - объект класса модели.

### Конструкторы

```explicit ServerViewModel(QObject *parent)``` - В него передается указатель на объект-предок для соблюдения принципов иерархического создания и удаления объектов. Здесь же инициализируется объект ```server_model```. В теле конструктора соединяются сигналы ```clientName```, ```errorServer```, ```sendMsgToGUI``` и ```removeClientFromList```.

### Методы

##### public:

```bool getStateServerStarted() const```;
```bool sendMsgToClient(const QString& message) const```;
```bool startServer(const QString& port) const```;
```bool stopServer() const```; 

Все перечисленные выше методы вызывают методы объекта ```server_model``` с теми же назвниями и возвращают те же значения.

### Сигналы

```void clientName(QString)```;
```void errorServer(QString)```;
```void sendMsgToGUI(QString)```;
```void removeClientFromList(QString)```;

Все сигналы идентичны сигналам с теми же названиями в ```server_model```.

---

## ServerView

Класс представления сервера.

### Атрибуты

```ServerViewModel *server_view_model``` - объект класса модели-представления.
```bool stateServerStarted{ false }``` - статус работы сервра.

### Конструкторы

##### public:

```explicit ServerView(QObject *parent)``` - В него передается указатель на объект-предок для соблюдения принципов иерархического создания и удаления объектов. Здесь же инициализируется объект ```server_view_model```. В теле метода соединяются сигналы ```clientName```, ```errorServer```, ```sendMsgToGUI```, ```removeClientFromList```.

### Методы

##### public:

```bool getStateServerStarted() const```;
```Q_INVOKABLE bool sendMsgToClient(const QString& message) const```;
```Q_INVOKABLE void startServer(const QString& port)```;
```Q_INVOKABLE void stopServer()```; - вызывают соответсвующие методы у объекта ```server_view_model```,  возвращая его же значеня.
```Q_INVOKABLE QString getCurrentDateTime() const```- возвращает текущие дату и время.

### Сигналы

```void clientName(QString)``` - сигнал, содержащий имя клиента.
```void errorServer(QString)``` - сигнал об ошибке с передачей строки с ее описанием.
```void messageSended(const QString&)``` - сигнал об успешной отправке сообщения клиенту и вывод сообщения в графический интерфейс.
```void sendMsgToGUI(QString)``` - сигнал, отправляющий текст сообщения на графический интерфейс.
```void removeClientFromList(QString)``` -  сигнал, отправляющий имя клиента в графический интерфейс для его последующего удления из списка.
```void stateServerStartedChanged(bool)``` - сигнал с новым статусом работы сервера.

---

## MessagesDB

Класс для работы с базой данных.

### Атрибуты

##### private:

```QSqlDatabase messages_db``` - объект класса для управления базой данных.
```bool stateDB``` - статус открытия базы данных.

### Конструкторы

##### public:

```explicit MessagesDB(QObject *parent, const QString &host, const QString &username)``` - В него передается указатель на объект-предок для соблюдения принципов  иерархического создания и удаления объектов, адрес сервера и имя клиента. В теле конструктора вызывается метод ```openDatabase```, возвращаемый резульятат которого присваивается атрибуту ```stateDB```.

### Деструкторы

```~MessagesDB()``` - закрывает базу данных и удаляет объект.

### Методы

##### public:

```void addMessage(const QString& sender_name, const QString& sender_address, const QString& msg)``` - добавляет сообщение в базу данных при помощи SQL запроса.

```void closeDatabase()```- закрывает базу данных.

```bool dbIsOpen() const```- возвращает статус открытия базы данных.

##### private:

```bool openDatabase(const QString &name_file_db, const QString &host, const QString &username)``` - в этот метод передаются имя файла базы данных, адрес сервера и имя клиента. Происходит открытие базы данных с входными параметрами.
