#include <inviwo/qt/editor/transferfunctioneditor.h>

namespace inviwo {
	TransferFunctionEditor::TransferFunctionEditor(PropertyWidgetQt *parent, TransferFunction* transferFunc, std::vector<TransferFunctionEditorControlPoint*>* points)
		:
	transferFunction_(transferFunc),
		parent_(parent),
		points_(points)
	{

	}

	TransferFunctionEditor::~TransferFunctionEditor(){}

	void TransferFunctionEditor::mousePressEvent(QGraphicsSceneMouseEvent *e){
		std::vector<TransferFunctionEditorControlPoint*>::iterator iter = points_->begin();

		if (e->button() == Qt::LeftButton){
			if(!e->modifiers().testFlag(Qt::ControlModifier)){
				for (iter = points_->begin(); iter != points_->end(); iter++){
					(*iter)->setSelected(false);
				}
			}
			if (itemAt(e->scenePos()) == NULL || itemAt(e->scenePos())->type() == TransferFunctionEditorLineItem::Type){
				addPoint(e);
			}
			else{
				QGraphicsScene::mousePressEvent(e); // this forwards the event to the item
			}
		}
		else if (e->button() == Qt::RightButton){
			if (itemAt(e->scenePos()) == NULL){}
			else if (itemAt(e->scenePos())->type() == TransferFunctionEditorControlPoint::Type){
				removePoint(e);
			}
			for (iter = points_->begin(); iter != points_->end(); iter++){
				(*iter)->setSelected(false);
			}
		}
		parent_->updateFromProperty();
	}

	void TransferFunctionEditor::mouseMoveEvent(QGraphicsSceneMouseEvent *e){
		QGraphicsScene::mouseMoveEvent(e);
		transferFunction_->sortDataPoints();
		transferFunction_->calcTransferValues();
		parent_->updateFromProperty();
		sortLines();
		this->update();	
	}

	void TransferFunctionEditor::addPoint(QGraphicsSceneMouseEvent *e){
		vec2* pos = new vec2(e->scenePos().x(), e->scenePos().y());
		pos->x = floor(pos->x + 0.5f);
		vec4* rgba = new vec4(e->scenePos().y()/100.0f);
		TransferFunctionDataPoint* newPoint = new TransferFunctionDataPoint(pos, rgba);
		transferFunction_->addPoint(newPoint);
		points_->push_back(new TransferFunctionEditorControlPoint(newPoint));
		addItem(points_->back());
		if (transferFunction_->getSize() > 1){
			lines_.push_back(new TransferFunctionEditorLineItem(
				transferFunction_->getPoint(transferFunction_->getSize()-2), 
				transferFunction_->getPoint(transferFunction_->getSize()-1)));
			addItem(lines_.back());
		}
		sortLines();
		points_->back()->setSelected(true);
		parent_->updateFromProperty();
		this->update();
	}

	void TransferFunctionEditor::removePoint(QGraphicsSceneMouseEvent *e){
		TransferFunctionEditorControlPoint* target = (TransferFunctionEditorControlPoint*)itemAt(e->scenePos());
		std::vector<TransferFunctionEditorControlPoint*>::iterator iter = points_->begin();
		if (!lines_.empty()){		
			lines_.back()->setVisible(false);
			lines_.pop_back();
		}
		for (iter = points_->begin(); iter != points_->end(); iter++){
			if (target->pos() == (*iter)->pos()){
				transferFunction_->removePoint((*iter)->getPoint());
				(*iter)->setVisible(false);
				points_->erase(iter);
				break;
			}
		}
		transferFunction_->sortDataPoints();
		transferFunction_->calcTransferValues();
		sortLines();
		parent_->updateFromProperty();
		this->update();
	}

	void TransferFunctionEditor::sortLines(){
		for (int i = 0; i < transferFunction_->getSize() - 1; i++){
			lines_[i]->setStart(transferFunction_->getPoint(i));
			lines_[i]->setFinish(transferFunction_->getPoint(i+1));
		}
	}
};