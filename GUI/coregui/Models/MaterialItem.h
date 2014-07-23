#ifndef MATERIALITEM_H
#define MATERIALITEM_H



#include "ParameterizedItem.h"
#include <QColor>

class MaterialItem : public ParameterizedItem
{
    Q_OBJECT
public:

    static const QString P_MATERIAL_TYPE, P_COLOR, P_REFRACTIVE_INDEX, P_MAGNETIC_FIELD, P_IDENTIFIER;
    explicit MaterialItem(ParameterizedItem *parent=0);
    ~MaterialItem(){}
    void setMaterialType(int index);

    QString getIdentifier() const;

    QColor getColor() const;

    bool isHomogeneousMaterial() const;

    bool isHomogeneousMagneticMaterial() const;
};








//#include "MaterialProperties.h"
//#include <QString>
//#include <QStringList>
//#include <QColor>
//#include <QMap>
//#include <QVariant>
//#include <QMetaType>
//#include <QPixmap>

//class QXmlStreamWriter;
//class QXmlStreamReader;


//class MaterialItem : public QObject
//{
//    Q_OBJECT

//public:
//    enum MaterialType {
//        HomogeneousMaterial,
//        HomogeneousMagneticMaterial,
//        SubItem
//    };

//    MaterialItem(const QString &name=QString(), MaterialType type = HomogeneousMaterial);
//    ~MaterialItem();
//    QString getName() const { return m_name; }
//    void setName(const QString &name);
//    void setType(MaterialType type);
//    void setType(QString typeName);
//    MaterialType getType() const { return m_type; }
//    QString getTypeName() const { return m_type_names.at(int(m_type)); }

//    QStringList getMaterialTypes() const;

//    virtual QString getTitleString() { return QString(); }

//    QMap<QString, MaterialItem *> getSubItems() const {
//        return m_sub_items;
//    }

//    bool event(QEvent * e );

//    void updateProperties();

//    bool setMaterialProperty(QString name, const QVariant &value);

//    virtual void writeTo(QXmlStreamWriter *writer);

//    virtual void writeProperty(QXmlStreamWriter *writer, MaterialItem *item, const char *property_name) const;

//    void writeSubProperty(QXmlStreamWriter *writer, MaterialItem *item) const;

//    void readFrom(QXmlStreamReader *reader);
//    QString readProperty(QXmlStreamReader *reader, MaterialItem *item);

//    void setRefractiveIndex(double delta, double beta);

//signals:
//    void propertyChanged(QString propertyName);
//    void propertyItemChanged(QString propertyName);

//public slots:
//    void onPropertyItemChanged(QString propertyName);

//private:
//    void addSubProperty(QString name);
//    void removeSubProperty(QString name);
//    void addColorProperty();

//    QString m_name;
//    MaterialType m_type;
//    static QStringList m_type_names;
//    QMap<QString, MaterialItem *> m_sub_items;
//};


//class RefractiveIndexItem : public MaterialItem
//{
//    Q_OBJECT

//public:
//    RefractiveIndexItem() : MaterialItem(MaterialProperties::RefractiveIndex, MaterialItem::SubItem)
//    {
//        setProperty("delta", QString("1e-3"));
//        setProperty("beta", QString("1e-5"));
//    }

//    QString getTitleString()
//    {
//        return QString("(1.0 - %1, %2)").arg(property("delta").toString(), property("beta").toString());
//    }
//};


//class MagneticFieldProperty : public MaterialItem
//{
//    Q_OBJECT

//public:
//    MagneticFieldProperty() : MaterialItem(MaterialProperties::MagneticField, MaterialItem::SubItem)
//    {
//        setProperty("Bx", 0.0);
//        setProperty("By", 0.0);
//        setProperty("Bz", 0.0);
//    }

//    QString getTitleString()
//    {
//        return QString("(%1, %2, %3)").arg(property("Bx").toString(), property("By").toString(), property("Bz").toString());
//    }
//};





#endif
