function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6417\" class=\"headerLeftMenuInActive\"><a id=\"aID6417\" href=\"#\" OnMouseOver=\"link('_dir','controller0',this)\" class=\"leftMenuLinkHeadInActive\">controller</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6416\" class=\"leftMenuInActive\"><a id=\"aID6416\" href=\"#\" OnMouseOver=\"link('_dir','character/character0',this)\" class=\"leftMenuLinkInActive\">character</a></div>\n");
document.write("<div id=\"divID6418\" class=\"leftMenuInActive\"><a id=\"aID6418\" href=\"#\" OnMouseOver=\"link('_dir','free/free0',this)\" class=\"leftMenuLinkInActive\">free</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID938\" class=\"leftMenuInActive\"><a id=\"aID938\" href=\"#\" OnMouseOver=\"link('_class','Controller35940',this)\" class=\"leftMenuLinkInActive\">Controller</a></div>\n");
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
