function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6311\" class=\"headerLeftMenuInActive\"><a id=\"aID6311\" href=\"#\" OnMouseOver=\"link('_dir','class0',this)\" class=\"leftMenuLinkHeadInActive\">class</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID791\" class=\"leftMenuInActive\"><a id=\"aID791\" href=\"#\" OnMouseOver=\"link('_class','Class53261',this)\" class=\"leftMenuLinkInActive\">Class</a></div>\n");
document.write("<div id=\"divID792\" class=\"leftMenuInActive\"><a id=\"aID792\" href=\"#\" OnMouseOver=\"link('_class','ClassSerializer53261',this)\" class=\"leftMenuLinkInActive\">ClassSerializer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Structs</div>\n");
document.write("<div id=\"divID790\" class=\"leftMenuInActive\"><a id=\"aID790\" href=\"#\" OnMouseOver=\"link('_class','Attribute53261',this)\" class=\"leftMenuLinkInActive\">Attribute</a></div>\n");
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
