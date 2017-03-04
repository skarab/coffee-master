function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6376\" class=\"headerLeftMenuInActive\"><a id=\"aID6376\" href=\"#\" OnMouseOver=\"link('_dir','mesh0',this)\" class=\"leftMenuLinkHeadInActive\">mesh</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6377\" class=\"leftMenuInActive\"><a id=\"aID6377\" href=\"#\" OnMouseOver=\"link('_dir','vertex_buffer/vertex_buffer0',this)\" class=\"leftMenuLinkInActive\">vertex_buffer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID883\" class=\"leftMenuInActive\"><a id=\"aID883\" href=\"#\" OnMouseOver=\"link('_class','Mesh54809',this)\" class=\"leftMenuLinkInActive\">Mesh</a></div>\n");
document.write("<div id=\"divID884\" class=\"leftMenuInActive\"><a id=\"aID884\" href=\"#\" OnMouseOver=\"link('_class','MeshSurface54809',this)\" class=\"leftMenuLinkInActive\">MeshSurface</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
