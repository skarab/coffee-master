function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6400\" class=\"headerLeftMenuInActive\"><a id=\"aID6400\" href=\"#\" OnMouseOver=\"link('_dir','cylinder0',this)\" class=\"leftMenuLinkHeadInActive\">cylinder</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID919\" class=\"leftMenuInActive\"><a id=\"aID919\" href=\"#\" OnMouseOver=\"link('_class','Cylinder14855',this)\" class=\"leftMenuLinkInActive\">Cylinder</a></div>\n");
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
