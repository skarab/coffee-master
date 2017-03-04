function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6346\" class=\"headerLeftMenuInActive\"><a id=\"aID6346\" href=\"#\" OnMouseOver=\"link('_dir','component0',this)\" class=\"leftMenuLinkHeadInActive\">component</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6345\" class=\"leftMenuInActive\"><a id=\"aID6345\" href=\"#\" OnMouseOver=\"link('_dir','camera/camera0',this)\" class=\"leftMenuLinkInActive\">camera</a></div>\n");
document.write("<div id=\"divID6348\" class=\"leftMenuInActive\"><a id=\"aID6348\" href=\"#\" OnMouseOver=\"link('_dir','light/light0',this)\" class=\"leftMenuLinkInActive\">light</a></div>\n");
document.write("<div id=\"divID6352\" class=\"leftMenuInActive\"><a id=\"aID6352\" href=\"#\" OnMouseOver=\"link('_dir','mesh/mesh0',this)\" class=\"leftMenuLinkInActive\">mesh</a></div>\n");
document.write("<div id=\"divID6353\" class=\"leftMenuInActive\"><a id=\"aID6353\" href=\"#\" OnMouseOver=\"link('_dir','sky/sky0',this)\" class=\"leftMenuLinkInActive\">sky</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID848\" class=\"leftMenuInActive\"><a id=\"aID848\" href=\"#\" OnMouseOver=\"link('_class','Component54809',this)\" class=\"leftMenuLinkInActive\">Component</a></div>\n");
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
