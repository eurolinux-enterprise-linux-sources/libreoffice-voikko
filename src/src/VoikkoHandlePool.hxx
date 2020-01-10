/* Libreoffice-voikko: Finnish linguistic extension for LibreOffice
 * Copyright (C) 2010 Harri Pitkänen <hatapitk@iki.fi>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef _VOIKKOHANDLEPOOL_HXX_
#define _VOIKKOHANDLEPOOL_HXX_

#include <libvoikko/voikko.h>
#include <map>
#include <com/sun/star/lang/Locale.hpp>
#include <string>

namespace voikko {

//using namespace ::rtl;
using namespace ::com::sun::star;

class VoikkoHandlePool {
	public:
		static VoikkoHandlePool * getInstance();
		
		VoikkoHandle * getHandle(const lang::Locale & locale);
		
		void closeAllHandles();
		
		void setGlobalBooleanOption(int option, bool value);
		
		void setGlobalIntegerOption(int option, int value);
		
		/**
		 * Set the preferred dictionary variant (private use tag) that
		 * will be used for all languages. If the specified variant is not
		 * available for given language then standard variant is used
		 * as a fallback.
		 */
		void setPreferredGlobalVariant(const rtl::OUString & variant);
		
		void setInstallationPath(const rtl::OString & path);
		
		const char * getInstallationPath();
		
		rtl::OUString getPreferredGlobalVariant();
		
		uno::Sequence<lang::Locale> getSupportedSpellingLocales();
		
		uno::Sequence<lang::Locale> getSupportedHyphenationLocales();
		
		uno::Sequence<lang::Locale> getSupportedGrammarLocales();
		
		bool supportsSpellingLocale(const lang::Locale & locale);
		
		bool supportsHyphenationLocale(const lang::Locale & locale);
		
		bool supportsGrammarLocale(const lang::Locale & locale);
		
		/** Returns initialization status diagnostics */
		rtl::OUString getInitializationStatus();
	private:
		VoikkoHandlePool();
		VoikkoHandle * openHandle(const rtl::OString & language);
		VoikkoHandle * openHandleWithVariant(const rtl::OString & language, const rtl::OString & fullVariant);
		void addLocale(uno::Sequence<lang::Locale> & locales, const char * language);
		std::map<rtl::OString, VoikkoHandle *> handles;
		std::map<rtl::OString, const char *> initializationErrors;
		std::map<int, bool> globalBooleanOptions;
		std::map<int, int> globalIntegerOptions;
		std::multimap<std::string, std::pair<std::string, std::string> > bcpToOOoMap;
		rtl::OUString preferredGlobalVariant;
		rtl::OString installationPath;
		static VoikkoHandlePool * instance;
};

}

#endif
