#include "DinasourGameMainWidget.h"
#include "core/DifficultyManager.h"
#include "core/EventManager.h"
#include "core/FlushRequester.h"
#include "core/ObstacleListManager.h"
#include "core/ObstacleType.h"
#include "core/ScoreManager.h"
#include "core/SoundEffectPlayer.h"
#include "figure/dinasour/Dinasour.h"
#include "figure/obstacle/Obsticals.h"
#include "settings/setting_scene.h"
#include "ui/SceneDrawer.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
DinasourGameMainWidget::DinasourGameMainWidget(QWidget* parent)
	: QWidget { parent } {
	setFixedSize(Settings::Scene::SCENE_FIXED_SZ.first,
				 Settings::Scene::SCENE_FIXED_SZ.second);
	init_memory();
	init_connection();
}

void DinasourGameMainWidget::launch_game() {
	game_start = true;
	dinasour->set_providing_state(Dinasour::State::RUNNING);
	scoreManager->set_increase_automatically(true);
	difficulty_manager->set_auto_update(true);
	obstacleManager->start_blank_working();
	sceneDrawer->setDrawHello(false);
	/* a jump hooks the game start */
	process_jump();
	emit game_started();
}

void DinasourGameMainWidget::process_jump() {
	dinasour->make_jump();
	soundEffectPlayer->play(SoundEffectPlayer::EffectIndex::JUMP);
}

void DinasourGameMainWidget::process_lay() {
	dinasour->set_laying(true);
}

DinasourGameMainWidget::CurrentInfoPack DinasourGameMainWidget::infoPack() const {
	return { scoreManager->get_score(), difficulty_manager->get_current_difficulty() };
}

void DinasourGameMainWidget::gain_score(ObstacleType type) {
	soundEffectPlayer->play(SoundEffectPlayer::EffectIndex::SCORE);
	int add_score = 0;
	switch (type) {
	case ObstacleType::UNKNOWN:
		break;
	case ObstacleType::SmallCactus:
		add_score = 10;
		break;
	case ObstacleType::MedCactus:
		add_score = 20;
		break;
	case ObstacleType::LargeCactus:
		add_score = 30;
		break;
	case ObstacleType::SmallBird:
		add_score = 20;
		break;
	case ObstacleType::MediumBird:
		add_score = 30;
		break;
	case ObstacleType::LargeBird:
		add_score = 40;
		break;
	}
	scoreManager->increase_once(add_score);
}

void DinasourGameMainWidget::pause() {
	scoreManager->set_increase_automatically(false);
	difficulty_manager->set_auto_update(false);
	scene_flush_once->set_flush_status(false);
}

void DinasourGameMainWidget::resume() {
	scoreManager->set_increase_automatically(true);
	difficulty_manager->set_auto_update(true);
	scene_flush_once->set_flush_status(true);
}

void DinasourGameMainWidget::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	sceneDrawer->bind_painter(&painter);
	sceneDrawer->drawSky();
	sceneDrawer->drawMainGround();

	int speed = obstacleManager->get_obstacle_speed();
	if (is_game_over() || !is_game_started()) {
		speed = 0;
	}
	sceneDrawer->drawFlowyGround(speed);
	sceneDrawer->drawDinasore(dinasour);
	auto obs = obstacleManager->get_should_render();
	sceneDrawer->drawObstical(obs);
	sceneDrawer->drawContent(scoreManager->get_score(),
							 difficulty_manager->get_current_difficulty());
}

void DinasourGameMainWidget::keyPressEvent(QKeyEvent* event) {
	eventManager->install_keyPress_keyEvent(event);
	switch (eventManager->indication()) {
	case EventManager::Indication::NOTHING:
		break;
	case EventManager::Indication::JUMP:
		process_jump();
		break;
	case EventManager::Indication::LAUNCH_GAME:
		launch_game();
		break;
	case EventManager::Indication::LAY:
		process_lay();
		break;
	}
	QWidget::keyPressEvent(event);
}

void DinasourGameMainWidget::keyReleaseEvent(QKeyEvent* event) {
	eventManager->install_keyRelease_keyEvent(event);
	auto res = eventManager->release_indication();
	switch (res) {
	case EventManager::KeyReleaseIndication::NOTHING:
		break;
	case EventManager::KeyReleaseIndication::RELAX:
		animate_up();
		break;
	}

	QWidget::keyReleaseEvent(event);
}

void DinasourGameMainWidget::mousePressEvent(QMouseEvent* event) {
	eventManager->install_mousepress_event(event);
	switch (eventManager->indication()) {
	case EventManager::Indication::NOTHING:
		break;
	case EventManager::Indication::JUMP:
		process_jump();
		break;
	case EventManager::Indication::LAUNCH_GAME:
		launch_game();
		break;
	case EventManager::Indication::LAY:
		process_lay();
		break;
	}
	QWidget::mousePressEvent(event);
}

void DinasourGameMainWidget::init_memory() {
	soundEffectPlayer = new SoundEffectPlayer(this);
	dinasour = new Dinasour(this);
	eventManager = std::make_shared<EventManager>(this);
	scoreManager = new ScoreManager(this);
	difficulty_manager = new DifficultyManager(this);
	obstacleManager = new ObstacleListManager(this);
	scene_flush_once = new FlushRequester(this);
	sceneDrawer = new SceneDrawer(rect());
	using namespace Settings::Scene;
	scene_flush_once->setRequestFlushInterval(SCENE_FLUSH_HZ);
	scene_flush_once->set_flush_status(true);
}

void DinasourGameMainWidget::init_connection() {
	connect(scene_flush_once, &FlushRequester::flush_once,
			this, &DinasourGameMainWidget::update_game);
	connect(obstacleManager, &ObstacleListManager::pass_a_obstacle,
			this, &DinasourGameMainWidget::gain_score);
	connect(difficulty_manager, &DifficultyManager::new_obstacle_cnt_max, obstacleManager,
			&ObstacleListManager::set_max_obstacle_cnt);
	connect(difficulty_manager, &DifficultyManager::new_move_speed, obstacleManager,
			&ObstacleListManager::set_obstacle_speed);
}

void DinasourGameMainWidget::update_game() {
	if (game_over)
		return;
	auto& dino = dinasour->provide_current_bounding_rect();
	dinasour->process_animation();

	if (game_start) {
		obstacleManager->animate_once();
	}

	if (obstacleManager->is_intersects(dinasour)) {
		process_die();
	}

	update();
}

void DinasourGameMainWidget::process_die() {
	game_over = true;
	scoreManager->set_increase_automatically(false);
	difficulty_manager->set_auto_update(false);
	scene_flush_once->set_flush_status(false);

	soundEffectPlayer->play(SoundEffectPlayer::EffectIndex::DIE);
	dinasour->set_providing_state(Dinasour::State::DIE);
	emit game_overed();
}

void DinasourGameMainWidget::clearAndReset() {
	difficulty_manager->force_reset();
	scoreManager->force_reset();
	obstacleManager->reset_back();
	game_over = false;
	game_start = false;
	scene_flush_once->set_flush_status(true);
	dinasour->set_providing_state(Dinasour::State::RUNNING);
}

void DinasourGameMainWidget::animate_up() {
	dinasour->set_laying(false);
}
