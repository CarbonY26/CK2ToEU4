#include "Religions.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
#include "Religion.h"

CK2::Religions::Religions(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void CK2::Religions::registerKeys()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& religionName, std::istream& theStream) {
		auto newReligion = Religion(theStream);
		reformedReligions.emplace(std::pair(religionName, newReligion.getFeatures()));
	});
}
