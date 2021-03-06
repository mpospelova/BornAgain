#include "google_test.h"
#include "ExternalProperty.h"
#include "Comparators.h"
#include "test_utils.h"

class TestExternalProperty :  public ::testing::Test
{
public:
    ~TestExternalProperty();
    ExternalProperty propertyFromXML(const QString& buffer) {
        return TestUtils::propertyFromXML<ExternalProperty>(buffer);
    }

};

TestExternalProperty::~TestExternalProperty() = default;

TEST_F(TestExternalProperty, test_initialState)
{
    ExternalProperty property;
    EXPECT_TRUE(property.isValid() == false);
    EXPECT_TRUE(property.color().isValid() == false);
    EXPECT_TRUE(property.identifier().isEmpty() == true);
    EXPECT_TRUE(property.text().isEmpty() == true);

    // changing any property should change state to valid
    property.setColor(QColor(Qt::red));
    EXPECT_TRUE(property.color() == QColor(Qt::red));
    EXPECT_TRUE(property.isValid() == true);
    property.setColor(QColor());
    EXPECT_TRUE(property.isValid() == false);
    property.setText("aaa");
    EXPECT_TRUE(property.text() == QString("aaa"));
    EXPECT_TRUE(property.isValid() == true);
    property.setText(QString());
    EXPECT_TRUE(property.isValid() == false);
}

//! Testing equality operators.

TEST_F(TestExternalProperty, test_equalityOperators)
{
    ExternalProperty prop1;
    ExternalProperty prop2;

    EXPECT_TRUE (prop1 == prop2);
    prop1.setColor(QColor(Qt::red));
    EXPECT_TRUE (prop1 != prop2);
    prop2.setColor(QColor(Qt::red));
    EXPECT_TRUE (prop1 == prop2);

    prop1.setIdentifier("aaa");
    EXPECT_TRUE (prop1 != prop2);
    prop2.setIdentifier("aaa");
    EXPECT_TRUE (prop1 == prop2);
}

//! Testing equality operators for QVariants based on ExternalProperty.
//! If comparators are not registered, the behavior is undefined

TEST_F(TestExternalProperty, test_variantEquality)
{
    ExternalProperty prop1;
    ExternalProperty prop2;

    if (Comparators::registered()) {
        EXPECT_TRUE(prop1.variant() == prop2.variant());
        prop1.setIdentifier("aaa");

        EXPECT_TRUE(prop1.variant() != prop2.variant());
        EXPECT_FALSE(prop1.variant() == prop2.variant());

        prop2.setIdentifier("aaa");

        EXPECT_TRUE(prop1.variant() == prop2.variant());
    }
}

TEST_F(TestExternalProperty, test_toXML)
{
    QString expected;

    // empty property to XML
    ExternalProperty property;
    expected = "<Parameter ParType=\"ExternalProperty\" ParRole=\"0\" Text=\"\" Color=\"\" Identifier=\"\"/>";
    EXPECT_EQ(TestUtils::propertyToXML(property), expected);

    // from XML to empty property
    EXPECT_EQ(propertyFromXML(expected).text(), property.text());
    EXPECT_EQ(propertyFromXML(expected).color(), property.color());
    EXPECT_EQ(propertyFromXML(expected).identifier(), property.identifier());
    EXPECT_TRUE(propertyFromXML(expected) == property);

    // initialized property to XML
    property.setIdentifier("{123456}");
    property.setText("abc");
    property.setColor(QColor(Qt::red));
    expected = "<Parameter ParType=\"ExternalProperty\" ParRole=\"0\" Text=\"abc\" Color=\"#ffff0000\" Identifier=\"{123456}\"/>";
    EXPECT_EQ(TestUtils::propertyToXML(property), expected);

    // from XML to initialized property
    EXPECT_EQ(propertyFromXML(expected).identifier(), property.identifier());
    EXPECT_EQ(propertyFromXML(expected).text(), property.text());
    EXPECT_EQ(propertyFromXML(expected).color(), property.color());
    EXPECT_TRUE(propertyFromXML(expected) == property);
}
