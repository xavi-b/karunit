TRANSLATIONS += \
    $$PWD/fr_FR.ts

CONFIG += lrelease embed_translations
QM_FILES_RESOURCE_PREFIX = translations
PRE_TARGETDEPS += compiler_lrelease_make_all

qm_file.files = $$files($$[QT_INSTALL_TRANSLATIONS]/qtbase_*.qm)
qm_file.base = $$[QT_INSTALL_TRANSLATIONS]
qm_file.prefix = qt_translations
RESOURCES += qm_file
