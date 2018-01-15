/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2017 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#include <modules/animationqt/sequenceeditorpanel/keyframeeditorwidget.h>
#include <modules/animationqt/sequenceeditorpanel/sequenceeditorwidget.h>
#include <modules/animation/datastructures/propertytrack.h>

#include <modules/qtwidgets/properties/ordinalpropertywidgetqt.h>

#include <inviwo/core/properties/property.h>
#include <inviwo/core/properties/propertywidgetfactory.h>

#include <warn/push>
#include <warn/ignore/all>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <warn/pop>

namespace inviwo {

namespace animation {
KeyframeEditorWidget::KeyframeEditorWidget(Keyframe &keyframe, SequenceEditorWidget *parent)
    : QWidget(parent), keyframe_(keyframe), sequenceEditorWidget_(parent) {

    auto layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Keyframe"));

    auto layout2 = new QHBoxLayout();
    layout->addLayout(layout2);

    auto timeSpinner = new QDoubleSpinBox();
    timeSpinner->setValue(keyframe.getTime().count());
    timeSpinner->setSuffix("s");
    timeSpinner->setSingleStep(0.1);
    timeSpinner->setDecimals(5);
    layout2->addWidget(timeSpinner);

    if (auto track = dynamic_cast<BasePropertyTrack *>(&parent->getTrack())) {
        property_.reset(track->getProperty()->clone());
        property_->setOwner(nullptr);
        
        auto propWidget =
            util::getInviwoApplication()->getPropertyWidgetFactory()->create(property_.get());
        propertyWidget_ = static_cast<PropertyWidgetQt *>(propWidget.release());

        if (auto label = propertyWidget_->findChild<EditableLabelQt *>()) {
            label->setVisible(false);
        }

        layout2->addWidget(propertyWidget_);
    }

    setLayout(layout);
}
}  // namespace animation

}  // namespace inviwo