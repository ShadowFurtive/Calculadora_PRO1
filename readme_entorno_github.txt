1. CONFIGURAR GITHUB PARA TRABAJAR EN ENTORNO COLABORATIVO Y CON CONTROL DE VERSIONES

1.1. Date de alta en GitHub
	http://github.com

1.2. Enviame tu username o tu dirección de correo en GitHub para que te añada como colaborador

1.3. Instala git en tu maquina linux
	apt-get install git

1.4. Configura tu usuario de git
	git config --global user.name "aqui_tu_usuario_de_git"

1.5. Configura tu correo de git
	git config --global user.email "aqui_tu_correo_de_git"

1.6. Inicialitza el repositorio
	git init practica_PRO1

1.6.1 Entra al directori local
	cd practica_PRO1

1.7. Añade el repositorio remoto
	git remote add practica1 https://github.com/ShadowFurtive/Practica_PRO1

1.8. Recibe en local los archivos remotos 
	git pull practica1 master

2. PROGRAMA

2.1. Programa localmente la aplicación
2.2. Documenta cada cosa que hagas
2.3. Compila
2.4. Ejecuta
2.5. Comprueba
2.6. Verifica

3. SUBIR TUS CAMBIOS Y CONTRIBUCIONES AL REPOSITORIO

3.1. Sube los cambios locales al repositorio remoto
	git add * // para subir al repo todos los archivos que contengan cambios
	git add [nombre_archivo] // para subgir al repo solo [nombre_archivo] si tiene cambios
	git commit -m "[añomesdiahoraminutos]_[tu_nombre_o_alias]__[etiqueta_sintetica_y_descriptiva_de_la_aportacion_realizada]"
	git push practica1 master

4. IR AL PASO 2








0. SOLO OCR. PARA REALIZAR RESTAURACIONES EN EL REPO

0.1. Sincronizar con la rama principal
	git pull --rebase activitat1 master

0.2 Restaurar archivos
	git log --oneline o chequeamos los commits desde la web
	
	0.2.1. Localizamos el codigo de commit del que deseamos restaurar
	0.2.2. Para restaurar un archivo
		git checkout codigo_commit nombre_archivo
		git add nombre_archivo
		git commit -m "nombre_archivo restaurado a commit codigo_commit"

0.3 Borrar archivos en repositorio remoto

	git rm -rf [remote_file_name]




