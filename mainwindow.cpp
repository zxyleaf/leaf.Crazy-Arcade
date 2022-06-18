#include "mainwindow.h"
#include <map.h>
#include <player.h>
#include <robot.h>
#include <ammo.h>
#include <gameobject.h>
#include <mypushbutton.h>
#include <imagetransform.h>
#include <shooter.h>
#include <physics.h>
#include <usercontroller.h>
#include <QVector>
#include <QPushButton>
#include <summondummy.h>
#include <transformbuilder.h>
#include <QPainter>
#include <QTimer>
#include <QPen>
#include <QSoundEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include "./ui_mainwindow.h"
#include <QDebug>
MainWindow *Mainone;
QGraphicsView * view;
QTimer * nowtime;
int page;
MyPushButton *s;
MyPushButton *t;
QSoundEffect * bk;
MyPushButton *b;
const char* getId(int id)
{
    if (id == 1) return ":/res/box09.png";
    if (id == 2) return ":/res/basket.png";
    if (id == 3) return ":/res/basket2.png";
    if (id == 4) return ":/res/box08.png";
    if (id == 5) return ":/res/box2.png";
    if (id == 6) return ":/res/block_box08.png";
    if (id == 7) return ":/res/pirate.png";
    if (id == 8) return ":/res/goldbox.png";
    if (id == 11) return ":/res/pirate_007_center.png";
    return " ";
}
int MainWindow::myclock()
{
    second++;
    pretimelist = timelist;
    auto tr = pretimelist->getComponent<Transform>();
    Q_ASSERT(tr != nullptr);
    auto boardTransform = new Transform(tr->pos());
    gameScene->detachGameObject(pretimelist);
    auto text = new QGraphicsSimpleTextItem(boardTransform);
    QFont f;
    f.setWeight(QFont::Black);
    f.setFamily(QStringLiteral("黑体"));
    f.setPointSize(14);
    text->setFont(f);
    text->setText(QString::number(1000 - second));
    text->setBrush(Qt::black);
    auto obj = new GameObject();
    obj->addComponent(boardTransform);
    //pretimelist->destory(pretimelist);
    timelist = obj;
    gameScene->attachGameObject(timelist);
    return second;
}
void MainWindow::loadScene(GameScene *gameScene) {
    second = 0;
    nowtime = new QTimer(this);
    connect(nowtime, &QTimer::timeout, this, &MainWindow::myclock);
    nowtime->start(1000);
    map *mm = new map;
    auto map = new GameObject();
    ImageTransformBuilder()
        .setPos(QPointF(-1, -1))
        .setImage(":/res/background.png")
        .setAlignment(Qt::AlignTop)// Qt::AlignLeft  Qt::AlignRight  右边缘对齐Qt::AlignHCenter 中心水平放在空间 Qt::AlignJustify	  为可用空间的文本排版
        .addToGameObject(map);
    gameScene->attachGameObject(map);
    auto end = new GameObject();
    auto tr = ImageTransformBuilder()
            .setPos(QPointF(1110, 700))
            .setImage(":/res/pause.png")
            .setAlignment(Qt::AlignHCenter)
            .setAlignment(Qt::AlignVCenter)// Qt::AlignLeft  Qt::AlignRight  右边缘对齐Qt::AlignHCenter 中心水平放在空间 Qt::AlignJustify	  为可用空间的文本排版
            .build();
    end->addComponent(tr);
    tr->setType(80);
    end->addComponent(new SummonDummy);
    gameScene->attachGameObject(end);
    for (int i = 0; i < 15; i++)
    {
        for (int k = 0, j = 50; k < 20; k++)
        {
            auto shooter = new GameObject();
            ImageTransformBuilder()
                .setPos(QPointF(j, (i+1) * 50))
                .setImage(":/res/mapfloor.png")
                .setAlignment(Qt::AlignHCenter)
                .setAlignment(Qt::AlignVCenter)// Qt::AlignLeft  Qt::AlignRight  右边缘对齐Qt::AlignHCenter 中心水平放在空间 Qt::AlignJustify	  为可用空间的文本排版
                .addToGameObject(shooter);
            gameScene->attachGameObject(shooter);
            j += 50;
        }
    }
    for (int i = 0, ix = 50; i < 15; i++, ix+= 50)
    {
        for (int j = 0, iy = 50; j < 20; j++, iy += 50)
        {
            auto cube = new GameObject();
            cube->addComponent(new Physics(i, j, mm));
            ImageTransformBuilder()
                .setPos(QPointF(iy, ix))
                .setImage(getId(mm->getmap(i, j)))
                .setType(mm->getmap(i, j))
                .setAlignment(Qt::AlignHCenter)
                .setAlignment(Qt::AlignVCenter)// Qt::AlignLeft  Qt::AlignRight  右边缘对齐Qt::AlignHCenter 中心水平放在空间 Qt::AlignJustify	  为可用空间的文本排版
                .addToGameObject(cube);
            if(mm->getmaptool(i, j) != 0)
                cube->addComponent(new Ammo(mm, mm->getmaptool(i, j), j, i));
            mm->Maplist.emplace_back(cube);
            gameScene->attachGameObject(cube);
        }
    }
  auto robot1 = new GameObject();
  robot1->addComponent(ImageTransformBuilder()
      .setPos(QPointF(250, 550))
      .setType(110)
      .setImage(":/res/robotS.png")
      .setAlignment(Qt::AlignHCenter)
      .setAlignment(Qt::AlignVCenter)
      .build());
  //auto r1 = new Robot(mm, 100, 700, 1, 13, 1);
  auto r1 = new Robot(mm, 250, 550, 4, 10, 1);
    robot1->addComponent(r1);
    gameScene->attachGameObject(robot1);
  auto robot2 = new GameObject();
    robot2->addComponent(ImageTransformBuilder()
        .setPos(QPointF(800, 250))
        .setType(110)
        .setImage(":/res/robot1s.png")
        .setAlignment(Qt::AlignHCenter)
        .setAlignment(Qt::AlignVCenter)
        .build());
    //auto r2 = new Robot(mm, 950, 100, 18, 1, 2);
    auto r2 = new Robot(mm, 800, 250, 15, 4, 2);
      robot2->addComponent(r2);
      gameScene->attachGameObject(robot2);
  auto player1 = new GameObject();
  player1->addComponent(ImageTransformBuilder()
      .setPos(QPointF(250, 250))
      .setType(100)
      .setImage(":/res/unit_monster_S.png")
      .setAlignment(Qt::AlignHCenter)
      .setAlignment(Qt::AlignVCenter)
      .build());
  //auto p1 = new Player(mm, 50, 50, 0, 0, 1);
  auto p1 = new Player(mm, 250, 250, 4, 4, 1);
  player1->addComponent(p1);
  gameScene->attachGameObject(player1);

  auto player2 = new GameObject();
  player2->addComponent(ImageTransformBuilder()
      .setPos(QPointF(800, 550))
      .setType(100)
      .setImage(":/res/monster2s2.png")
      .setAlignment(Qt::AlignHCenter)
      .setAlignment(Qt::AlignVCenter)
      .build());
  //auto p2 = new Player(mm, 1000, 750, 19, 14, 2);
  auto p2 = new Player(mm, 800, 550, 15, 10, 2);
    player2->addComponent(p2);
  gameScene->attachGameObject(player2);

  auto music = new GameObject();
  auto transform2 = new Transform();
  auto musicbtn = new QGraphicsPixmapItem(transform2);
  musicbtn->setPixmap(QPixmap(":/res/music.png"));
  musicbtn->setOffset(0,0);
  transform2->setPos(1020, 710);
  transform2->setType(70);
  music->addComponent(transform2);
  music->addComponent(new SummonDummy);
  gameScene->attachGameObject (music);

  auto back = new GameObject();
  auto transform = new Transform();
  auto startbtn = new QGraphicsPixmapItem(transform);
  startbtn->setPixmap(QPixmap(":/res/back.png"));
  startbtn->setOffset(0,0);
  transform->setPos(1156, 720);
  transform->setType(3);
  back->addComponent(transform);
  back->addComponent(new SummonDummy);
  gameScene->attachGameObject (back);

  int j = 1200, k = 126;
  for (int ty = 15; ty >= 11; ty--)
  {
      if (ty != 15)
          k = 43 + 26 * (4 - (ty - 10)), j = 1300;
      for (int time = 1;time <= 4; time++, k = k + 136)
      {
          auto text1 = new GameObject();
          auto boardTransform = new Transform(QPointF(j, k));
          boardTransform->setType(ty);
          text1->addComponent(boardTransform);
          auto text = new QGraphicsSimpleTextItem(boardTransform);
          if (ty == 15)
              text->setText("0");
          else
              text->setText("1");
          text->setBrush(Qt::black);
          QFont f;
          f.setWeight(QFont::Black);
          f.setFamily(QStringLiteral("黑体"));
          f.setPointSize(14);
          text->setFont(f);
          if (time == 1)
              p1->mainboard.emplace_back(text1);
          else if (time == 2)
              p2->mainboard.emplace_back(text1);
          else if (time == 3)
              r1->mainboard.emplace_back(text1);
          else if (time == 4)
              r2->mainboard.emplace_back(text1);
          gameScene->attachGameObject(text1);
      }

  }
}
void MainWindow::loadScene2(GameScene *gameScene)
{
    auto map = new GameObject();
    ImageTransformBuilder()
        .setPos(QPointF(0, 0))
        .setImage(":/res/controller.png")
        .setAlignment(Qt::AlignTop)// Qt::AlignLeft  Qt::AlignRight  右边缘对齐Qt::AlignHCenter 中心水平放在空间 Qt::AlignJustify	  为可用空间的文本排版
        .addToGameObject(map);
    gameScene->attachGameObject(map);
    auto back = new GameObject();
    auto transform = new Transform();
    auto startbtn = new QGraphicsPixmapItem(transform);
    startbtn->setPixmap(QPixmap(":/res/back.png"));
    startbtn->setOffset(0,0);
    transform->setPos(361, 642);
    transform->setType(3);
    back->addComponent(transform);
    back->addComponent(new SummonDummy);
    gameScene->attachGameObject (back);
    auto power = new GameObject();
    auto transformp = new Transform();
    auto powerbtn = new QGraphicsPixmapItem(transformp);
    powerbtn->setPixmap(QPixmap(":/res/poweup.png"));
    powerbtn->setOffset(0,0);
    transformp->setPos(796, 631);
    transformp->setType(4);
    power->addComponent(transformp);
    power->addComponent(new SummonDummy);
    gameScene->attachGameObject (power);
}
void MainWindow::loadScenetool(GameScene *gameScene)
{
    auto map = new GameObject();
    ImageTransformBuilder()
        .setPos(QPointF(0, 0))
        .setImage(":/res/tollguide.png")
        .setAlignment(Qt::AlignTop)// Qt::AlignLeft  Qt::AlignRight  右边缘对齐Qt::AlignHCenter 中心水平放在空间 Qt::AlignJustify	  为可用空间的文本排版
        .addToGameObject(map);
    gameScene->attachGameObject(map);
    auto back = new GameObject();
    auto transform = new Transform();
    auto startbtn = new QGraphicsPixmapItem(transform);
    startbtn->setPixmap(QPixmap(":/res/back.png"));
    startbtn->setOffset(0,0);
    transform->setPos(370, 602);
    transform->setType(3);
    back->addComponent(transform);
    back->addComponent(new SummonDummy);
    gameScene->attachGameObject (back);
    auto power = new GameObject();
    auto transformp = new Transform();
    auto powerbtn = new QGraphicsPixmapItem(transformp);
    powerbtn->setPixmap(QPixmap(":/res/controllerpage.png"));
    powerbtn->setOffset(0,0);
    transformp->setPos(840, 602);
    transformp->setType(5);
    power->addComponent(transformp);
    power->addComponent(new SummonDummy);
    gameScene->attachGameObject (power);
}
void MainWindow::loadScene1(GameScene *gameScene)
{
    auto map = new GameObject();
    ImageTransformBuilder()
        .setPos(QPointF(0, 0))
        .setImage(":/res/begin.png")
        .setAlignment(Qt::AlignTop)// Qt::AlignLeft  Qt::AlignRight  右边缘对齐Qt::AlignHCenter 中心水平放在空间 Qt::AlignJustify	  为可用空间的文本排版
        .addToGameObject(map);
    gameScene->attachGameObject(map);
    s = new MyPushButton(":/res/start1.png");
    t = new MyPushButton(":/res/tools.png");
    b = new MyPushButton(":/res/back.png");
    s->setParent(view);
    s->move(300, 280);
    connect(s, &MyPushButton::clicked,[=](){
        s->zoom1();
        s->zoom2();
        QTimer::singleShot(100, this,[=]()mutable{

            if (nowtime != nullptr)
              nowtime->stop();
            Mainone->disconnect(nowtime,0,0,0);
            auto game2 = new GameScene();
      //      auto gameScene2 = new GameScene();
            Mainone->gameScene = game2;
            Mainone->gameScene->setParent(Mainone);
            view->setScene(game2);
            view->setFrameStyle(QFrame::NoFrame);
            view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
            view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
            page = 2;
            auto boardTransform = new Transform(QPointF(1270, 620));
            auto text = new QGraphicsSimpleTextItem(boardTransform);
            QFont f;
            f.setWeight(QFont::Black);
            f.setFamily(QStringLiteral("楷体"));
            f.setPointSize(14);
            text->setFont(f);
            text->setText("1000");
            text->setBrush(Qt::black);
            auto text1 = new GameObject();
            text1->addComponent(boardTransform);
            Mainone->timelist = text1;
            Mainone->gameScene->attachGameObject(Mainone->timelist);
            Mainone->loadScene(game2);
            s->hide();
            t->hide();
            b->hide();
            //this->show();
        });
    });


    t->setParent(view);
    t->move(300, 370);
    connect(t, &MyPushButton::clicked,[=](){
        t->zoom1();
        t->zoom2();
        //qDebug() <<"lookhowtoplay";
        QTimer::singleShot(50, this,[=]()mutable{
            auto game2 = new GameScene();
            Mainone->gameScene = game2;
            Mainone->gameScene->setParent(Mainone);
            view->setScene(game2);
            view->setFrameStyle(QFrame::NoFrame);
            view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
            view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
            page = 3, Mainone->loadScene2(game2);
            t->hide();
            s->hide();
            b->hide();
         });
    });
    b->setParent(view);
    b->move(320, 470);
    connect(b, &MyPushButton::clicked,[=](){
        b->zoom1();
        b->zoom2();
        //qDebug() <<"lookhowtoplay";
        QTimer::singleShot(50, this,[=]()mutable{
            auto game2 = new GameScene();
            this->close();
            t->hide();
            s->hide();
            b->hide();
         });
    });
    if (Mainone->begin == 0)
    {
        QTimer::singleShot(250, this,[=]()mutable{
            bk = new QSoundEffect;
            bk->setSource(QUrl::fromLocalFile(":/res/bg_ad_001.wav"));
            bk->setLoopCount(50);
            bk->setVolume(0.1f);
            bk->play();
        });
        Mainone->begin = 1;
    }

}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(1400,800);
  setWindowIcon(QIcon("://res/BnB_icon_r2_144.png"));
  setWindowTitle("zxy的Q版泡泡堂");
  Mainone = this;
  page = 1;
  auto game1 = new GameScene();
  gameScene = game1;
  gameScene->setParent(this);
  view = new QGraphicsView(gameScene, this);
  view->setFrameStyle(QFrame::NoFrame);
  view->resize(this->size());
  view->setSceneRect(QRect(0, 0, this->width(), this->height()));
  view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  loadScene1(gameScene);
}

MainWindow::~MainWindow() { delete ui; }
