#!/bin/bash

VERSION_FILE="include/version.h"

# Lê a versão atual
CURRENT_VERSION=$(grep "#define TDS_VERSION_STRING" $VERSION_FILE | awk '{print $3}' | tr -d '"')

# Separa versão MAJOR.MINOR.PATCH
IFS='.' read -r MAJOR MINOR PATCH <<< "$CURRENT_VERSION"

echo "Versão atual: $CURRENT_VERSION"
echo "Escolha o tipo de atualização:"
echo "1) PATCH  (Correções)"
echo "2) MINOR  (Novas funcionalidades)"
echo "3) MAJOR  (Mudança incompatível)"
read -p "Selecione (1/2/3): " choice

case $choice in
    1) PATCH=$((PATCH + 1)) ;;
    2) MINOR=$((MINOR + 1)); PATCH=0 ;;
    3) MAJOR=$((MAJOR + 1)); MINOR=0; PATCH=0 ;;
    *) echo "Opção inválida"; exit 1 ;;
esac

NEW_VERSION="$MAJOR.$MINOR.$PATCH"

# Atualiza o arquivo version.h
sed -i "s/#define TDS_VERSION_STRING \"$CURRENT_VERSION\"/#define TDS_VERSION_STRING \"$NEW_VERSION\"/" $VERSION_FILE
sed -i "s/#define TDS_VERSION_MAJOR $MAJOR/#define TDS_VERSION_MAJOR $MAJOR/" $VERSION_FILE
sed -i "s/#define TDS_VERSION_MINOR $MINOR/#define TDS_VERSION_MINOR $MINOR/" $VERSION_FILE
sed -i "s/#define TDS_VERSION_PATCH $PATCH/#define TDS_VERSION_PATCH $PATCH/" $VERSION_FILE

# Commit, tag e push no Git
git add $VERSION_FILE
git commit -m "chore: Atualizando versão para $NEW_VERSION"
git tag -a "v$NEW_VERSION" -m "Versão $NEW_VERSION"
git push origin main --tags

echo "✅ Versão atualizada para $NEW_VERSION"

# Como usar?
# chmod +x bump_version.sh
# ./bump_version.sh
